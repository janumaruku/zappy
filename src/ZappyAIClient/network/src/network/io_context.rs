use colored::Colorize;
use libc::{POLLERR, POLLHUP, POLLIN, POLLNVAL, POLLOUT, nfds_t, poll, pollfd};
use std::cell::RefCell;
use std::collections::{HashMap, VecDeque};
use std::rc::Rc;

#[derive(PartialEq)]
enum OpType {
    Read,
    Write,
}

#[derive(Default)]
pub struct IoContext {
    pollfds: Vec<pollfd>,
    pending_operations: HashMap<i32, VecDeque<(OpType, Box<dyn FnOnce() + 'static>)>>,
    running: bool,
    stop: bool,
}

impl IoContext {
    pub fn new() -> Rc<RefCell<IoContext>> {
        Rc::new(RefCell::new(IoContext::default()))
    }

    pub fn register_file_descriptor(&mut self, fd: i32) {
        self.pollfds.push(pollfd {
            fd,
            events: 0,
            revents: 0,
        });

        self.pending_operations.insert(fd, VecDeque::new());
    }

    pub fn unregister_file_descriptor(&mut self, fd: i32) {
        let itt = self
            .pollfds
            .iter()
            .enumerate()
            .find(|(_, pfd)| pfd.fd == fd);

        match itt {
            None => {}
            Some((i, _)) => {
                self.pollfds.remove(i);
                self.pending_operations.remove(&fd);
            }
        }
    }

    pub fn post_read(&mut self, fd: i32, handler: impl FnOnce() + 'static) {
        if let Some(queue) = self.pending_operations.get_mut(&fd) {
            queue.push_back((OpType::Read, Box::new(handler)));
        }
        self.update_event_type(fd);
    }

    pub fn post_write(&mut self, fd: i32, handler: impl FnOnce() + 'static) {
        if let Some(queue) = self.pending_operations.get_mut(&fd) {
            queue.push_back((OpType::Write, Box::new(handler)));
        }
        self.update_event_type(fd);
    }

    fn update_event_type(&mut self, fd: i32) {
        let event = match self
            .pending_operations
            .get(&fd)
            .and_then(|queue| queue.front())
        {
            None => 0,
            Some((OpType::Read, _)) => POLLIN,
            Some((OpType::Write, _)) => POLLOUT,
        };

        if let Some(pfd) = self.pollfds.iter_mut().find(|pfd| pfd.fd == fd) {
            pfd.events = event;
        }
    }

    pub fn run(this: Rc<RefCell<Self>>) -> Result<(), String> {
        this.borrow_mut().running = true;

        loop {
            let result = unsafe {
                let mut context = this.borrow_mut();
                poll(
                    context.pollfds.as_mut_ptr(),
                    context.pollfds.len() as nfds_t,
                    10,
                )
            };
            if result == -1 {
                this.borrow_mut().running = false;
                return Err("Failed to poll".to_string());
            }

            Self::handle_ready_file_descriptor(Rc::clone(&this));

            {
                let context = this.borrow();
                if context.stop
                    && context
                        .pending_operations
                        .iter()
                        .all(|(_, queue)| queue.is_empty())
                {
                    break;
                }
            }
        }

        this.borrow_mut().running = false;

        Ok(())
    }

    pub fn stop(&mut self) {
        self.stop = true;
    }

    pub fn poll(this: Rc<RefCell<Self>>) -> Result<(), String> {
        if this.borrow().running {
            return Err(format!(
                "{}The IOContext loop is already running.",
                "Error: ".red()
            ));
        }

        {
            let mut context = this.borrow_mut();
            if unsafe {
                poll(
                    context.pollfds.as_mut_ptr(),
                    context.pollfds.len() as nfds_t,
                    10,
                ) == -1
            } {
                return Err(format!(
                    "{}Failed to poll the file descriptors.",
                    "Error: ".red()
                ));
            }
        }

        Self::handle_ready_file_descriptor(Rc::clone(&this));

        Ok(())
    }

    pub fn poll_all(this: Rc<RefCell<Self>>) -> Result<(), String> {
        if this.borrow().running {
            return Err(format!(
                "{}The IOContext loop is already running.",
                "Error: ".red()
            ));
        }

        loop {
            let n = {
                let mut context = this.borrow_mut();
                unsafe {
                    poll(
                        context.pollfds.as_mut_ptr(),
                        context.pollfds.len() as nfds_t,
                        0,
                    )
                }
            };
            if n <= 0 {
                break;
            }

            Self::handle_ready_file_descriptor(Rc::clone(&this));
        }

        Ok(())
    }

    fn handle_ready_file_descriptor(this: Rc<RefCell<Self>>) {
        let mut i = 0;

        loop {
            let len = this.borrow().pollfds.len();
            if i >= len {
                break;
            }

            let (temp_fd, revents) = {
                let context = this.borrow();
                (context.pollfds[i].fd, context.pollfds[i].revents)
            };

            if revents & (POLLHUP | POLLERR | POLLNVAL) != 0 {
                let mut context = this.borrow_mut();
                context.pending_operations.remove(&temp_fd);
                context.pollfds.remove(i);
                continue;
            }

            Self::trigger_handler(Rc::clone(&this), i);

            let (stop, empty) = {
                let context = this.borrow();
                (context.stop, context.pollfds.is_empty())
            };
            if stop && empty {
                break;
            }

            i += 1;
        }
    }

    fn trigger_handler(this: Rc<RefCell<Self>>, i: usize) {
        let revents = this.borrow().pollfds[i].revents;

        if revents & (POLLIN | POLLOUT) == 0 {
            return;
        }

        let fd = this.borrow().pollfds[i].fd;
        let temp_handler = {
            let mut context = this.borrow_mut();
            context
                .pending_operations
                .get_mut(&fd)
                .and_then(|queue| queue.pop_front())
                .map(|(_, handler)| handler)
        };

        if let Some(handler) = temp_handler {
            handler();
            this.borrow_mut().update_event_type(fd);
        }
    }
}

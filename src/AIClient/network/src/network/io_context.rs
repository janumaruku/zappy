use colored::Colorize;
use libc::{POLLERR, POLLHUP, POLLIN, POLLNVAL, POLLOUT, nfds_t, poll, pollfd};
use std::collections::{HashMap, VecDeque};

#[derive(PartialEq)]
enum OpType {
    Read,
    Write,
}

#[derive(Default)]
pub struct IoContext {
    pollfds: Vec<pollfd>,
    pending_operations: HashMap<i32, VecDeque<(OpType, Box<dyn FnOnce() + Send + 'static>)>>,
    running: bool,
    stop: bool,
}

impl IoContext {
    pub fn new() -> Self {
        IoContext::default()
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

    pub fn post_read(&mut self, fd: i32, handler: Box<dyn FnOnce() + Send + 'static>) {
        if let Some(queue) = self.pending_operations.get_mut(&fd) {
            queue.push_back((OpType::Read, handler));
        }
        self.update_event_type(fd);
    }

    pub fn post_write(&mut self, fd: i32, handler: Box<dyn FnOnce() + Send + 'static>) {
        if let Some(queue) = self.pending_operations.get_mut(&fd) {
            queue.push_back((OpType::Write, handler));
        }
        self.update_event_type(fd);
    }

    fn update_event_type(&mut self, fd: i32) {
        let event = match self.pending_operations.get(&fd).and_then(|queue| queue.front()) {
            None => 0,
            Some((OpType::Read, _)) => POLLIN,
            Some(&(OpType::Write, _)) => POLLOUT,
        };
        
        if let Some(pfd) = self.pollfds.iter_mut().find(|pfd| pfd.fd == fd) {
            pfd.events = event;
        }
    }

    pub fn run(&mut self) -> Result<(), String> {
        self.running = true;

        loop {
            unsafe {
                if poll(self.pollfds.as_mut_ptr(), self.pollfds.len() as nfds_t, 10) == -1 {
                    self.running = false;
                    return Err("Failed to poll".to_string());
                }
            }
            self.handle_ready_file_descriptor();

            if self.stop
                && self
                    .pending_operations
                    .iter()
                    .all(|(_, queue)| queue.is_empty())
            {
                break;
            }
        }

        self.running = false;

        Ok(())
    }

    pub fn stop(&mut self) {
        self.stop = true;
    }

    pub fn poll(&mut self) -> Result<(), String> {
        if self.running {
            return Err(format!(
                "{}The IOContext loop is already running.",
                "Error: ".red()
            ));
        }

        unsafe {
            if poll(self.pollfds.as_mut_ptr(), self.pollfds.len() as nfds_t, 10) == -1 {
                return Err(format!(
                    "{}Failed to poll the file descriptors.",
                    "Error: ".red()
                ));
            }
        }

        self.handle_ready_file_descriptor();

        Ok(())
    }

    pub fn poll_all(&mut self) -> Result<(), String> {
        if self.running {
            return Err(format!(
                "{}The IOContext loop is already running.",
                "Error: ".red()
            ));
        }

        while unsafe { poll(self.pollfds.as_mut_ptr(), self.pollfds.len() as nfds_t, 0) > 0 } {
            self.handle_ready_file_descriptor();
        }

        Ok(())
    }

    fn handle_ready_file_descriptor(&mut self) {
        let mut i = 0;

        while i < self.pollfds.len() {
            if self.pollfds[i].revents & (POLLHUP | POLLERR | POLLNVAL) != 0 {
                self.pending_operations.remove(&self.pollfds[i].fd);
                self.pollfds.remove(i);
                continue;
            }

            self.trigger_handler(i);

            if self.stop && self.pollfds.is_empty() {
                break;
            }

            i += 1;
        }
    }

    fn trigger_handler(&mut self, i: usize) {
        let fd = self.pollfds[i].fd;

        if self.pollfds[i].revents & (POLLIN | POLLOUT) == 0 {
            return;
        }

        if let Some(queue) = self.pending_operations.get_mut(&fd) {
            if let Some((_, handler)) = queue.pop_front() {
                handler();
                self.update_event_type(fd);
            }
        }
    }
}

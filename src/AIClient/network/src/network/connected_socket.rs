use crate::network::{Endpoint, IoContext, NetworkError};
use libc::{
    AF_INET, SOCK_STREAM, close, connect, read, size_t, sockaddr, socket, socklen_t, write,
};
use std::cell::RefCell;
use std::ffi::c_void;
use std::rc::{Rc, Weak};

pub struct ConnectedSocket {
    socket_fd: i32,
    endpoint: Endpoint,
    io_context: Rc<RefCell<IoContext>>,
    self_ref: Weak<RefCell<ConnectedSocket>>,
}

pub struct SocketConfig {
    pub io_context: Rc<RefCell<IoContext>>,
    pub fd: i32,
    pub endpoint: Endpoint,
}

impl ConnectedSocket {
    pub fn new(
        io_context: Rc<RefCell<IoContext>>,
    ) -> Result<Rc<RefCell<ConnectedSocket>>, NetworkError> {
        let fd = unsafe { socket(AF_INET, SOCK_STREAM, 0) };
        if fd < 0 {
            Err(NetworkError::SocketOpenFailed(
                "ConnectedSocket".to_string(),
            ))
        } else {
            let socket = Rc::new(RefCell::new(ConnectedSocket {
                socket_fd: fd,
                endpoint: Endpoint::new(0, ""),
                io_context,
                self_ref: Weak::new(),
            }));

            let fd = socket.borrow().socket_fd;
            socket
                .borrow_mut()
                .io_context
                .borrow_mut()
                .register_file_descriptor(fd);
            socket.borrow_mut().self_ref = Rc::downgrade(&socket);

            Ok(socket)
        }
    }

    pub fn from_socket_config(config: SocketConfig) -> Rc<RefCell<ConnectedSocket>> {
        let socket = Rc::new(RefCell::new(ConnectedSocket {
            socket_fd: config.fd,
            endpoint: config.endpoint,
            io_context: config.io_context,
            self_ref: Weak::new(),
        }));

        let fd = socket.borrow().socket_fd;
        socket
            .borrow_mut()
            .io_context
            .borrow_mut()
            .register_file_descriptor(fd);
        socket.borrow_mut().self_ref = Rc::downgrade(&socket);

        socket
    }

    pub fn get_self(&self) -> Option<Rc<RefCell<ConnectedSocket>>> {
        self.self_ref.upgrade()
    }

    pub fn connect(&mut self, endpoint: Endpoint) -> Result<(), NetworkError> {
        let address = endpoint.address();
        let address_size = size_of_val(&address);
        self.endpoint = endpoint;

        if unsafe {
            connect(
                self.socket_fd,
                &address as *const _ as *const sockaddr,
                address_size as socklen_t,
            ) == -1
        } {
            return Err(NetworkError::ConnectFailed("ConnectedSocket".to_string()));
        }

        Ok(())
    }

    pub fn socket_fd(&self) -> i32 {
        self.socket_fd
    }

    pub fn remote_endpoint(&self) -> String {
        format!("{}:{}", self.endpoint.host(), self.endpoint.port())
    }

    pub fn endpoint(&self) -> &Endpoint {
        &self.endpoint
    }

    pub fn close(&mut self) {
        unsafe { close(self.socket_fd) };
        self.io_context
            .borrow_mut()
            .unregister_file_descriptor(self.socket_fd);
    }

    pub fn write(
        &self,
        buffer: &[u8],
        handler: impl FnOnce(Option<Box<dyn std::error::Error>>, usize),
    ) {
        let bytes = unsafe {
            write(
                self.socket_fd,
                buffer.as_ptr() as *const c_void,
                buffer.len() as size_t,
            )
        };

        self.call_handler(bytes as i32, handler);
    }

    pub fn read(
        &self,
        buffer: &mut [u8],
        handler: impl FnOnce(Option<Box<dyn std::error::Error>>, usize),
    ) {
        let bytes = unsafe {
            read(
                self.socket_fd,
                buffer.as_mut_ptr() as *mut c_void,
                buffer.len() as size_t,
            )
        };

        self.call_handler(bytes as i32, handler);
    }

    fn call_handler(
        &self,
        bytes: i32,
        handler: impl FnOnce(Option<Box<dyn std::error::Error>>, usize),
    ) {
        match bytes {
            -1 => {
                let err = std::io::Error::last_os_error();
                handler(Some(Box::new(err)), 0);
            }
            n => handler(None, n as usize),
        }
    }

    pub fn async_read_some<B>(
        &mut self,
        buffer: Rc<RefCell<B>>,
        handler: impl FnOnce(Option<Box<dyn std::error::Error>>, usize) + 'static,
    ) where
        B: AsMut<[u8]> + 'static,
    {
        let socket_ref = self.self_ref.clone();
        let buffer_ref = Rc::clone(&buffer);

        self.io_context
            .borrow_mut()
            .post_read(self.socket_fd, move || {
                let Some(socket) = socket_ref.upgrade() else {
                    return;
                };

                let bytes = unsafe {
                    let mut buf = buffer_ref.borrow_mut();
                    let slice = buf.as_mut();

                    read(
                        socket.borrow().socket_fd,
                        slice.as_mut_ptr() as *mut c_void,
                        slice.len() as size_t,
                    )
                };

                socket.borrow().call_handler(bytes as i32, handler);
            });
    }

    pub fn async_write<B>(
        &mut self,
        buffer: B,
        handler: impl FnOnce(Option<Box<dyn std::error::Error>>, usize) + 'static,
    ) where
        B: AsRef<[u8]> + 'static,
    {
        let socket_ref = self.self_ref.clone();

        self.io_context
            .borrow_mut()
            .post_write(self.socket_fd, move || {
                let Some(socket) = socket_ref.upgrade() else {
                    return;
                };

                let slice = buffer.as_ref();

                let bytes = unsafe {
                    write(
                        socket.borrow().socket_fd,
                        slice.as_ptr() as *const c_void,
                        slice.len() as size_t,
                    )
                };

                socket.borrow().call_handler(bytes as i32, handler);
            });
    }
}

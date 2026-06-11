use crate::network::{
    AcceptorError, ConnectedSocket, Endpoint, IoContext, NetworkError, SocketConfig,
};
use libc::{accept, bind, listen, setsockopt, sockaddr, sockaddr_in, socket, socklen_t, AF_INET, SOCK_STREAM, SOL_SOCKET, SO_REUSEADDR};
use std::cell::RefCell;
use std::ffi::c_void;
use std::mem;
use std::rc::{Rc, Weak};

pub struct Acceptor {
    socket_fd: i32,
    endpoint: Endpoint,
    io_context: Rc<RefCell<IoContext>>,
    self_ref: Weak<RefCell<Acceptor>>,
}

impl Acceptor {
    pub fn new(
        io_context: Rc<RefCell<IoContext>>,
        endpoint: Endpoint,
    ) -> Result<Rc<RefCell<Acceptor>>, NetworkError> {
        let socket_fd = unsafe { socket(AF_INET, SOCK_STREAM, 0) };

        if socket_fd < 0 {
            return Err(NetworkError::AcceptError(AcceptorError::SocketOpenFailed));
        }

        let opt: i32 = 1;
        if unsafe {
            setsockopt(
                socket_fd,
                SOL_SOCKET,
                SO_REUSEADDR,
                &opt as *const i32 as *const c_void,
                size_of::<i32>() as socklen_t,
            )
        } == -1
        {
            return Err(NetworkError::AcceptError(AcceptorError::SocketOpenFailed));
        }

        let address = endpoint.address();
        if unsafe {
            bind(
                socket_fd,
                &address as *const _ as *const sockaddr,
                size_of::<sockaddr_in>() as socklen_t,
            )
        } == -1
        {
            return Err(NetworkError::AcceptError(AcceptorError::BindFailed));
        }

        if unsafe { listen(socket_fd, 128) } == -1 {
            return Err(NetworkError::AcceptError(AcceptorError::ListenFailed));
        }

        let acceptor = Rc::new(RefCell::new(Acceptor {
            socket_fd,
            endpoint,
            io_context,
            self_ref: Weak::new(),
        }));

        acceptor.borrow_mut().self_ref = Rc::downgrade(&acceptor);

        acceptor.borrow_mut().io_context.borrow_mut().register_file_descriptor(socket_fd);

        Ok(acceptor)
    }

    pub fn fd(&self) -> i32 {
        self.socket_fd
    }

    pub fn endpoint(&self) -> String {
        format!("{}:{}", self.endpoint.host(), self.endpoint.port())
    }

    pub fn async_accept(
        &mut self,
        handler: impl FnOnce(Result<Rc<RefCell<ConnectedSocket>>, NetworkError>) + 'static,
    ) {
        let weak_ref = self.self_ref.clone();
        self.io_context
            .borrow_mut()
            .post_read(self.socket_fd, move || {
                let Some(acceptor) = weak_ref.upgrade() else {
                    return;
                };
                let client_socket = accept_client(
                    acceptor.borrow().socket_fd,
                    acceptor.borrow().io_context.clone(),
                );

                match client_socket {
                    None => {
                        handler(Err(NetworkError::AcceptError(AcceptorError::InvalidState)));
                    }
                    Some(socket) => {
                        handler(Ok(socket))
                    }
                }
            })
    }
}

fn accept_client(
    socket_fd: i32,
    io_context: Rc<RefCell<IoContext>>,
) -> Option<Rc<RefCell<ConnectedSocket>>> {
    let mut address: sockaddr_in = unsafe { std::mem::zeroed() };
    let mut size = mem::size_of::<sockaddr_in>() as socklen_t;
    let client_fd = unsafe {
        accept(
            socket_fd,
            &mut address as *mut _ as *mut sockaddr,
            &mut size,
        )
    };

    if client_fd < 0 {
        None
    } else {
        Some(ConnectedSocket::from_socket_config(SocketConfig {
            io_context,
            fd: client_fd,
            endpoint: Endpoint::from_sockaddr(address),
        }))
    }
}

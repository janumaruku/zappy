use network::network::{ConnectedSocket, Endpoint, IoContext, NetworkError};
use std::cell::RefCell;
use std::rc::{Rc, Weak};

pub struct AiTcpClient {
    io_context: Rc<RefCell<IoContext>>,
    socket: Rc<RefCell<ConnectedSocket>>,
    read_buffer: Rc<RefCell<Vec<u8>>>,
    async_read_buffer: Rc<RefCell<Vec<u8>>>,
    transmission: String,
    transmission_temp: String,
    self_ref: Weak<RefCell<AiTcpClient>>,
}

impl AiTcpClient {
    pub fn new(
        io_context: Rc<RefCell<IoContext>>,
    ) -> Result<Rc<RefCell<AiTcpClient>>, NetworkError> {
        let socket = ConnectedSocket::new(Rc::clone(&io_context));
        match socket {
            Ok(socket) => {
                let tcp_client = Rc::new(RefCell::new(AiTcpClient {
                    io_context,
                    socket,
                    read_buffer: Rc::new(RefCell::new(vec![0; 1024])),
                    async_read_buffer: Rc::new(RefCell::new(vec![0; 1024])),
                    transmission: String::new(),
                    transmission_temp: String::new(),
                    self_ref: Weak::new(),
                }));

                tcp_client.borrow_mut().self_ref = Rc::downgrade(&tcp_client);

                Ok(tcp_client)
            }
            Err(err) => Err(err),
        }
    }

    pub fn start(&self) {
        if let Some(socket) = self.self_ref.upgrade() {
            AiTcpClient::start_read(socket);
        }
    }

    fn start_read(this: Rc<RefCell<AiTcpClient>>) {
        let copy_ref = this.clone();
        let buf_copy_ref = this.borrow().async_read_buffer.clone();
        let socket = this.borrow().socket.clone();

        socket
            .borrow_mut()
            .async_read_some(buf_copy_ref, move |err, bytes| {
                if let Some(err) = err {
                    eprintln!("{err}");
                    AiTcpClient::start_read(copy_ref.clone());
                    return;
                }

                if bytes == 0 {
                    println!("Client disconnected!");
                    copy_ref.borrow_mut().socket.borrow_mut().close();
                    return;
                }

                AiTcpClient::handle_transmission(copy_ref.clone(), bytes);
            })
    }

    fn handle_transmission(this: Rc<RefCell<AiTcpClient>>, bytes: usize) {
        {
            let mut mut_ref = this.borrow_mut();
            let data = mut_ref.async_read_buffer.borrow().clone();
            mut_ref
                .transmission
                .push_str(&String::from_utf8_lossy(&data[..bytes]));

            if mut_ref.transmission.ends_with("\n") {
                // ("process transmission here")
                mut_ref.transmission.clear();
                return;
            }
        }

        AiTcpClient::start_read(this);
    }

    pub fn send(&self, msg: String) {
        if let Some(self_ref) = self.self_ref.upgrade() {
            self.socket.borrow().write(msg.as_bytes(), |err, bytes| {
                if let Some(err) = err {
                    eprintln!("{err}");
                    return;
                }

                if bytes == 0 {
                    println!("Client disconnected!");
                    self_ref.borrow().socket.borrow_mut().close();
                    return;
                }

                println!("Send: {msg}");
            })
        }
    }

    pub fn receive(&mut self) -> String {
        let Some(self_ref) = self.self_ref.upgrade() else {
            return String::default();
        };

        let mut done = false;

        while !done {
            let mut bytes_received = 0usize;
            {
                let mut buf = self.read_buffer.borrow_mut();
                self.socket.borrow().read(buf.as_mut(), |err, bytes| {
                    if let Some(err) = err {
                        eprintln!("{err}");
                        done = true;
                        return;
                    }
                    if bytes == 0 {
                        println!("Client disconnected!");
                        self_ref.borrow().socket.borrow_mut().close();
                        done = true;
                        return;
                    }
                    bytes_received = bytes;
                });
            }

            if !done {
                done = self.is_transmission_ready(bytes_received);
            }
        }

        let result = std::mem::take(&mut self.transmission);
        println!("Received: {result}");
        result
    }

    fn is_transmission_ready(&mut self, bytes: usize) -> bool {
        let buf = self.read_buffer.borrow();
        let chunk = &buf[..bytes];
        let text = String::from_utf8_lossy(chunk);

        match text.find('\n') {
            None => {
                self.transmission.push_str(&text);
                false
            }
            Some(index) => {
                self.transmission.push_str(&text[..index]);

                let leftover = &text[index + 1..];
                if !leftover.is_empty() {
                    self.transmission_temp.push_str(leftover);
                }
                true
            }
        }
    }

    pub fn connect(&mut self, endpoint: Endpoint) -> Result<(), NetworkError> {
        self.socket.borrow_mut().connect(endpoint)
    }

    pub fn close(&mut self) {
        self.socket.borrow_mut().close();
    }
}

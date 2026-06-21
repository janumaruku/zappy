use network::network::{ConnectedSocket, Endpoint, IoContext, NetworkError};
use std::cell::RefCell;
use std::ops::Deref;
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
            let transmission = &format!("{}\n", &msg);
            self.socket.borrow().write(transmission.as_ref(), |err, bytes| {
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

    pub fn receive(&mut self) -> Option<String> {
        let Some(self_ref) = self.self_ref.upgrade() else {
            return None;
        };

        if let Some(idx) = self.transmission_temp.find('\n') {
            let line = self.transmission_temp[..idx].to_string();
            self.transmission_temp = self.transmission_temp[idx + 1..].to_string();
            println!("Received: {line}");
            return Some(line);
        }
        if !self.transmission_temp.is_empty() {
            self.transmission.push_str(&std::mem::take(&mut self.transmission_temp));
        }

        let mut done = false;
        let result = Rc::new(RefCell::new(None::<String>));
        let ref_result = result.clone();

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

            if done {
                break;
            }

            if self.is_transmission_ready(bytes_received) {
                *ref_result.borrow_mut() = Some(self.transmission.clone());
                self.transmission.clear();
                done = true;
            }
        }

        match result.borrow().clone() {
            None => None,
            Some(msg) => {
                println!("Received: {msg}");
                Some(msg)
            }
        }
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

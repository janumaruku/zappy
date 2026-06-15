use network::network::{ConnectedSocket, Endpoint, IoContext};
use std::cell::RefCell;
use std::rc::Rc;

fn main() {
    let io_context = IoContext::new();
    let socket = ConnectedSocket::new(Rc::clone(&io_context));
    match socket {
        Ok(socket) => {
            if let Err(e) = socket
                .borrow_mut()
                .connect(Endpoint::new(4242, "127.0.0.1"))
            {
                eprintln!("Failed to connect: {e}");
                return;
            }
            println!("Connected to 127.0.0.1:4242");

            let buffer = Rc::new(RefCell::new(vec![0u8; 1024]));
            let buffer_read = Rc::clone(&buffer);
            let io_ctx_stop = Rc::clone(&io_context);

            socket
                .borrow_mut()
                .async_read_some(buffer, move |err, bytes| {
                    match err {
                        Some(e) => eprintln!("Read error: {e}"),
                        None => {
                            let buf = buffer_read.borrow();
                            println!("Received: {}", String::from_utf8_lossy(&buf[..bytes]));
                        }
                    }
                    io_ctx_stop.borrow_mut().stop();
                });

            if let Err(e) = IoContext::run(Rc::clone(&io_context)) {
                eprintln!("Event loop error: {e}");
            }
        }
        Err(err) => eprintln!("Error: {}", err),
    }
}

use std::cell::RefCell;
use std::rc::Rc;
use network::network::{Acceptor, Endpoint, IoContext};

fn accept_loop(acceptor: Rc<RefCell<Acceptor>>) {
    let weak = Rc::downgrade(&acceptor);
    acceptor.borrow_mut().async_accept(move |result| {
        match result {
            Ok(socket) => {
                println!("Client connected: {}", socket.borrow().remote_endpoint());
                socket.borrow().write(b"Welcome!\n", |err, bytes| {
                    match err {
                        Some(e) => eprintln!("Write error: {e}"),
                        None => println!("Sent {bytes} bytes"),
                    }
                });
            }
            Err(e) => eprintln!("Accept error: {e}"),
        }
        if let Some(acc) = weak.upgrade() {
            accept_loop(acc);
        }
    });
}

fn main() {
    let io_context = IoContext::new();

    match Acceptor::new(Rc::clone(&io_context), Endpoint::new(4242, "127.0.0.1")) {
        Err(e) => eprintln!("Failed to start acceptor: {e}"),
        Ok(acceptor) => {
            println!("Listening on 127.0.0.1:4242");
            accept_loop(Rc::clone(&acceptor));
            if let Err(e) = IoContext::run(Rc::clone(&io_context)) {
                eprintln!("Event loop error: {e}");
            }
        }
    }
}

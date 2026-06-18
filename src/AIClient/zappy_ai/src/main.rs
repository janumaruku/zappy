use ai_tcp_client::AiTcpClient;
use network::network::{Endpoint, IoContext, NetworkError};
use shell::command::{CommandBuilder, CommandDefinition};
use std::cell::RefCell;
use std::rc::Rc;
use behavior_tree::behavior_tree::{BehaviorTree, BlackBoard};
use crate::ai_data::random_walk;

mod ai_data;

fn build_command(
    port: Rc<RefCell<i32>>,
    team: Rc<RefCell<String>>,
    hostname: Rc<RefCell<String>>,
) -> Result<CommandDefinition, String> {
    CommandBuilder::new()
        .name("zappy_ai")
        .description("Zappy AI agent. Drives the player on the map")
        .option(|builder| {
            builder
                .name("port")
                .alias('p')
                .description("Port number")
                .required()
        })
        .option(|builder| {
            builder
                .name("name")
                .alias('n')
                .description("Port number")
                .required()
        })
        .option(|builder| {
            builder
                .name("hostname")
                .alias('m')
                .description("Port number")
                .required()
        })
        .action(move |context| {
            *port.borrow_mut() = context.option("port").unwrap().parse().unwrap();
            *team.borrow_mut() = context.option("name").unwrap().to_string();
            *hostname.borrow_mut() = context.option("hostname").unwrap().to_string();
            println!("Port:\t\t{}", port.borrow());
            println!("Team:\t\t{}", team.borrow());
            println!("Hostname:\t{}", hostname.borrow());
        })
        .build()
}

fn handshake(port: i32, host: &str, team: &str) -> Result<Rc<RefCell<AiTcpClient>>, String> {
    let tcp_client = AiTcpClient::new(IoContext::new());

    match tcp_client {
        Ok(client) => {
            client
                .borrow_mut()
                .connect(Endpoint::new(port as u16, host))
                .expect("Player can not connect to remote endpoint");

            client.borrow_mut().receive();
            client.borrow().send(team.to_string());
            let num: i32 = client.borrow_mut().receive().parse().unwrap();
            if num <= 0 {
                client.borrow_mut().close();
                Err("No slot available. Player can not connect".to_string())
            } else {
                Ok(client)
            }
        }
        Err(err) => Err(err.to_string()),
    }
}

fn main() {
    let port = Rc::new(RefCell::new(0));
    let team = Rc::new(RefCell::new(String::new()));
    let hostname = Rc::new(RefCell::new(String::new()));

    let command = build_command(port.clone(), team.clone(), hostname.clone());
    let tokens: Vec<String> = std::env::args().collect();
    command.unwrap().run(&tokens);

    let tcp_client = handshake(*port.borrow(), &**hostname.borrow(), &**team.borrow());

    let mut behavior_tree = BehaviorTree::new(random_walk(tcp_client.unwrap().clone()));
    let mut bb = BlackBoard::new();

    loop {
        behavior_tree.tick(&mut bb);
    }
}

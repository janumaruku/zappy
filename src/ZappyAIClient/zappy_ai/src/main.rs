use crate::ai_data::{ServerMessage, build_tree, classify, random_walk, WorldModel};
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{BehaviorTree, BlackBoard};
use network::network::{Endpoint, IoContext, NetworkError};
use shell::command::{CommandBuilder, CommandDefinition};
use std::cell::RefCell;
use std::rc::Rc;

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
            let num: i32;
            if let Some(result) = client.borrow_mut().receive() {
                num = result.parse().unwrap();
            } else {
                return Err(String::from("Failed to receive"));
            }
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

fn parse_broadcast_level(text: &str) -> Option<u8> {
    let rest = text.strip_prefix("LVL")?;
    let end = rest.find(|c: char| !c.is_ascii_digit())?;
    rest[..end].parse::<u8>().ok()
}

fn main() {
    let port = Rc::new(RefCell::new(0));
    let team = Rc::new(RefCell::new(String::new()));
    let hostname = Rc::new(RefCell::new(String::new()));

    let command = build_command(port.clone(), team.clone(), hostname.clone());
    let tokens: Vec<String> = std::env::args().collect();
    command.unwrap().run(&tokens);

    let tcp_client: Rc<RefCell<AiTcpClient>>;
    {
        match handshake(*port.borrow(), &**hostname.borrow(), &**team.borrow()) {
            Ok(result) => tcp_client = result,
            Err(err) => {
                println!("{}", err);
                return;
            }
        }
    }

    let mut tree = build_tree(tcp_client.clone());
    let mut world = WorldModel::new();
    let mut bb = BlackBoard::new();
    tree.tick(&mut bb);

    loop {
        let transmission: String;
        if let Some(result) = tcp_client.borrow_mut().receive() {
            transmission = result;
        } else {
            continue;
        }

        let response = classify(&transmission);
        match response {
            ServerMessage::Dead => break,
            ServerMessage::Broadcast(k, text) => {
                bb.set("broadcast_k", k);
                bb.set("broadcast_text", text.clone());
                bb.set("broadcast_level", parse_broadcast_level(&text));
                bb.set("broadcast_timestamp", std::time::Instant::now());
            }
            ServerMessage::Eject(orientation) => {}
            _ => {
                bb.set("last_response", response.clone());
                world.update(&response, &mut bb);
                tree.tick(&mut bb);
            }
        }
        tree.tick(&mut bb);
    }
}

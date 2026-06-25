use crate::ai_data::{ServerMessage, build_tree, classify, WorldModel};
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{BehaviorTree, BlackBoard, NodeStatus};
use network::network::{Endpoint, IoContext};
use shell::command::{CommandBuilder, CommandDefinition};
use std::cell::RefCell;
use std::rc::Rc;

mod ai_data;
mod config;

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

fn handshake(port: i32, host: &str, team: &str) -> Result<(Rc<RefCell<AiTcpClient>>, u32, u32), String> {
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
                num = result.trim().parse().unwrap();
            } else {
                return Err(String::from("Failed to receive client number"));
            }
            if num <= 0 {
                client.borrow_mut().close();
                return Err("No slot available. Player can not connect".to_string());
            }

            let (width, height) = if let Some(dims) = client.borrow_mut().receive() {
                let parts: Vec<&str> = dims.trim().split_whitespace().collect();
                if parts.len() == 2 {
                    let w = parts[0].parse::<u32>().unwrap_or(0);
                    let h = parts[1].parse::<u32>().unwrap_or(0);
                    (w, h)
                } else {
                    return Err(format!("Unexpected map dimensions: {dims}"));
                }
            } else {
                return Err("Failed to receive map dimensions".to_string());
            };

            println!("[handshake] map: {width}x{height}");
            Ok((client, width, height))
        }
        Err(err) => Err(err.to_string()),
    }
}

fn parse_broadcast_level(text: &str) -> Option<u8> {
    let rest = text.strip_prefix("LVL")?;
    let end = rest.find(|c: char| !c.is_ascii_digit())?;
    rest[..end].parse::<u8>().ok()
}

fn tick_until_running(tree: &mut BehaviorTree, bb: &mut BlackBoard) {
    loop {
        match tree.tick(bb) {
            NodeStatus::Running => {
                println!("[tick] → Running, waiting for server response");
                break;
            }
            NodeStatus::Success => println!("[tick] → Success, re-ticking"),
            NodeStatus::Failure => println!("[tick] → Failure, re-ticking"),
        }
    }
}

fn main() {
    let port = Rc::new(RefCell::new(0));
    let team = Rc::new(RefCell::new(String::new()));
    let hostname = Rc::new(RefCell::new(String::new()));

    let command = build_command(port.clone(), team.clone(), hostname.clone());
    let tokens: Vec<String> = std::env::args().collect();
    command.unwrap().run(&tokens);

    let tcp_client: Rc<RefCell<AiTcpClient>>;
    let map_width: u32;
    let map_height: u32;
    {
        match handshake(*port.borrow(), &**hostname.borrow(), &**team.borrow()) {
            Ok((client, w, h)) => { tcp_client = client; map_width = w; map_height = h; }
            Err(err) => {
                println!("{}", err);
                return;
            }
        }
    }

    let mut tree = build_tree(tcp_client.clone());
    let mut world = WorldModel::new(map_width, map_height);
    let mut bb = BlackBoard::new();
    bb.set("map_width", map_width);
    bb.set("map_height", map_height);

    tick_until_running(&mut tree, &mut bb);

    loop {
        let transmission = match tcp_client.borrow_mut().receive() {
            Some(r) => r,
            None => break,
        };

        println!("[main] ← {:?}", transmission);
        let response = classify(&transmission);
        match response {
            ServerMessage::Dead => {
                println!("[main] server: dead → exiting");
                break;
            }
            ServerMessage::Broadcast(k, text) => {
                println!("[main] broadcast k={k}: {text:?} → blackboard only");
                bb.set("broadcast_k", k);
                bb.set("broadcast_text", text.clone());
                bb.set("broadcast_level", parse_broadcast_level(&text));
                bb.set("broadcast_timestamp", std::time::Instant::now());
            }
            ServerMessage::Eject(_) => {
                println!("[main] ejected → blackboard only");
                bb.set("was_ejected", true);
            }
            _ => {
                println!("[main] command response ({}) → world.update + tick", response.variant_name());
                world.update(&response, &mut bb);
                tick_until_running(&mut tree, &mut bb);
            }
        }
    }
}

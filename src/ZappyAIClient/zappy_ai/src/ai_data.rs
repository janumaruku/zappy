mod world_model;
mod zappy_tree_nodes;
mod server_message;

use std::cell::RefCell;
use std::rc::Rc;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{BehaviorTree, BlackBoard, SequenceNode};
pub use world_model::*;
pub use zappy_tree_nodes::*;
pub use server_message::*;

pub fn parse_broadcast_level(text: &str) -> Option<u8> {
    let rest = text.strip_prefix("LVL")?;
    let end = rest.find(|c: char| !c.is_ascii_digit())?;
    rest[..end].parse::<u8>().ok()
}

pub fn receive_command_response(
    client: &Rc<RefCell<AiTcpClient>>,
    world: &Rc<RefCell<WorldModel>>,
    bb: &mut BlackBoard,
) -> ServerMessage {
    loop {
        let line = match client.borrow_mut().receive() {
            None => return ServerMessage::Dead,
            Some(l) => l,
        };

        match classify(&line) {
            ServerMessage::Broadcast(k, text) => {
                bb.set("broadcast_k", k);
                bb.set("broadcast_text", text.clone());
                bb.set("broadcast_level", parse_broadcast_level(&text));
                bb.set("broadcast_timestamp", std::time::Instant::now());
            }
            ServerMessage::Eject(_) => {
                bb.set("was_ejected", true);
            }
            ServerMessage::Dead => return ServerMessage::Dead,
            msg => {
                world.borrow_mut().update(&msg, bb);
                return msg;
            }
        }
    }
}

pub fn build_tree(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
) -> BehaviorTree {
    BehaviorTree::new(
        Box::new(SequenceNode::new(vec![
            // survive_branch(client.clone(), world.clone()),
            random_walk(client.clone(), world.clone()),
        ]))
    )
}

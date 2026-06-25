mod world_model;
mod zappy_tree_nodes;
mod server_message;

use std::cell::RefCell;
use std::rc::Rc;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{BehaviorTree, BlackBoard, SequenceNode};
use behavior_tree::decorator_node::RunUntilNode;
pub use world_model::*;
pub use zappy_tree_nodes::*;
pub use server_message::*;

pub fn build_tree(client: Rc<RefCell<AiTcpClient>>) -> BehaviorTree {
    BehaviorTree::new(
        Box::new(RunUntilNode::new(
            |bb| {
                let found = matches!(bb.get::<Option<usize>>("food_target_tile"), Ok(Some(_)));
                println!("[run_until] food_target_tile found: {found}");
                found
            },
            Box::new(SequenceNode::new(vec![
                random_walk(client.clone()),
                look_action(client.clone()),
            ])),
        )),
    )
}

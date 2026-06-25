mod world_model;
mod zappy_tree_nodes;
mod server_message;

use std::cell::RefCell;
use std::rc::Rc;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{BehaviorNode, BehaviorTree, SelectorNode, SequenceNode};
pub use world_model::*;
pub use zappy_tree_nodes::*;
pub use server_message::*;

pub fn survive_branch(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SelectorNode::new(vec![
        Box::new(SequenceNode::new(vec![
            inventory_action(client.clone()),
            food_threshold_condition(),
        ])),
        food_seeking_sequence(client.clone()),
    ]))
}

pub fn build_tree(client: Rc<RefCell<AiTcpClient>>) -> BehaviorTree {
    BehaviorTree::new(Box::new(SequenceNode::new(vec![
        survive_branch(client.clone()),
        random_walk(client.clone()),
    ])))
}

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
    use behavior_tree::decorator_node::RunUntilNode;
    use crate::config::FOOD_SAFE_THRESHOLD;
    Box::new(SelectorNode::new(vec![
        Box::new(SequenceNode::new(vec![
            inventory_action(client.clone()),
            food_threshold_condition(),
        ])),
        Box::new(RunUntilNode::new(
            |bb| bb.get::<u32>("food").map(|v| *v >= FOOD_SAFE_THRESHOLD).unwrap_or(false),
            food_seeking_sequence(client.clone()),
        )),
    ]))
}

pub fn coordinate_branch(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SelectorNode::new(vec![
        Box::new(SequenceNode::new(vec![
            broadcast_received_condition(),
            broadcast_level_matches(),
            navigate_toward_k_action(client.clone()),
        ])),
        answer_elevation_sequence(client.clone()),
    ]))
}

pub fn elevate_branch(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        food_not_critical_condition(),
        Box::new(SelectorNode::new(vec![
            leader_elevation_sequence(client.clone()),
            coordinate_branch(client.clone()),
            stone_seeking_sequence(client.clone()),
        ])),
    ]))
}

pub fn build_tree(client: Rc<RefCell<AiTcpClient>>) -> BehaviorTree {
    BehaviorTree::new(Box::new(SequenceNode::new(vec![
        survive_branch(client.clone()),
        elevate_branch(client.clone()),
        random_walk(client.clone()),
    ])))
}

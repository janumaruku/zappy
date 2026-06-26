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

pub fn elevate_branch(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        food_not_critical_condition(),
        Box::new(SelectorNode::new(vec![
            Box::new(SequenceNode::new(vec![
                has_required_stones(),
                enough_teammates_on_tile(),
                food_not_critical_condition(),
                incantation_action(client.clone()),
            ])),
            wait_for_teammates_sequence(client.clone()),
            stone_seeking_sequence(client.clone()),
        ])),
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

pub fn build_tree(client: Rc<RefCell<AiTcpClient>>) -> BehaviorTree {
    BehaviorTree::new(Box::new(SequenceNode::new(vec![
        survive_branch(client.clone()),
        elevate_branch(client.clone()),
        coordinate_branch(client.clone()),
        random_walk(client.clone()),
    ])))
}

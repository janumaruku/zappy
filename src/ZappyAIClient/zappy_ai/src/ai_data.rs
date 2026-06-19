mod world_model;
mod zappy_tree_nodes;

use std::cell::RefCell;
use std::rc::Rc;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{BehaviorTree, BlackBoard};
pub use world_model::*;
pub use zappy_tree_nodes::*;

pub fn build_tree(client: Rc<RefCell<AiTcpClient>>) -> BehaviorTree {
    BehaviorTree::new(random_walk(client.clone()))
}

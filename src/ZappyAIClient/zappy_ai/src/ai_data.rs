mod world_model;
mod zappy_tree_nodes;
mod server_message;

use std::cell::RefCell;
use std::rc::Rc;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::BehaviorTree;
pub use world_model::*;
pub use zappy_tree_nodes::*;
pub use server_message::*;

pub fn build_tree(client: Rc<RefCell<AiTcpClient>>) -> BehaviorTree {
    BehaviorTree::new(food_seeking_sequence(client.clone()))
}

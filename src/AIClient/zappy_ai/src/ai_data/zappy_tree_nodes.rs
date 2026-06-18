use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{ActionNode, BehaviorNode, NodeStatus};
use rand::RngExt;
use std::cell::RefCell;
use std::rc::Rc;

pub fn random_walk(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(ActionNode::new(move |_| {
        let roll: f32 = rand::rng().random_range(0.0..1.0);

        let action = match roll {
            r if r < 0.6 => "Forward".to_string(),
            r if r < 0.8 => "Left".to_string(),
            _ => "Right".to_string(),
        };

        client.borrow().send(action);
        client.borrow_mut().receive();
        NodeStatus::Failure
    }))
}

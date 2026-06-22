use crate::ai_data::ServerMessage;
use crate::config::FOOD_SAFE_THRESHOLD;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{ActionNode, BehaviorNode, ConditionNode, NodeStatus};
use rand::RngExt;
use std::cell::RefCell;
use std::rc::Rc;

pub fn random_walk(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut sent = false;

    Box::new(ActionNode::new(move |bb| {
        if !sent {
            let roll: f32 = rand::rng().random_range(0.0..1.0);
            let cmd = match roll {
                r if r < 0.6 => "Forward",
                r if r < 0.8 => "Left",
                _ => "Right",
            };
            client.borrow().send(cmd.to_string());
            sent = true;
            return NodeStatus::Running;
        }

        sent = false;
        NodeStatus::Success
    }))
}

pub fn food_threshold_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| match bb.get::<u32>("food") {
        Ok(food) => *food >= FOOD_SAFE_THRESHOLD,
        Err(err) => {
            eprintln!("{err}");
            false
        }
    }))
}

pub fn look_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut flag = false;

    Box::new(ActionNode::new(move |bb| {
        if !flag {
            client.borrow().send("Look".to_string());
            flag = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Look(_)) => {
                match bb.clear("last_response") {
                    Ok(_) => {}
                    Err(err) => eprintln!("{err}"),
                };
                flag = false;
                NodeStatus::Success
            }
            Ok(_) => NodeStatus::Running,
            Err(err) => {
                eprintln!("{err}");
                NodeStatus::Running
            }
        }
    }))
}

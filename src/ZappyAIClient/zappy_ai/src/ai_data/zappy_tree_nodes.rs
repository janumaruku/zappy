use crate::ai_data::{ServerMessage, tile_to_commands};
use crate::config::FOOD_SAFE_THRESHOLD;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{
    ActionNode, BehaviorNode, ConditionNode, NodeStatus, SequenceNode,
};
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

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Ok) => {
                bb.clear("last_response").ok();
                sent = false;
                NodeStatus::Success
            }
            Ok(ServerMessage::Ko) => {
                bb.clear("last_response").ok();
                sent = false;
                NodeStatus::Failure
            }
            Ok(_) => NodeStatus::Running,
            Err(_) => NodeStatus::Running,
        }
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

pub fn navigate_to_tile_action(
    client: Rc<RefCell<AiTcpClient>>,
    tile_key: &'static str,
) -> Box<dyn BehaviorNode> {
    let mut commands: Vec<String> = Vec::new();
    let mut awaiting_response = false;

    Box::new(ActionNode::new(move |bb| {
        if commands.is_empty() && !awaiting_response {
            let tile_index = match bb.get::<Option<usize>>(&format!("{}_target_tile", tile_key)) {
                Ok(Some(idx)) => *idx,
                _ => return NodeStatus::Failure,
            };
            commands = tile_to_commands(tile_index);
            if commands.is_empty() {
                return NodeStatus::Success;
            }
        }

        if !awaiting_response {
            client.borrow().send(commands[0].clone());
            awaiting_response = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Ok) => {
                bb.clear("last_response").ok();
                commands.remove(0);
                awaiting_response = false;
                if commands.is_empty() {
                    NodeStatus::Success
                } else {
                    NodeStatus::Running
                }
            }
            Ok(ServerMessage::Ko) => {
                bb.clear("last_response").ok();
                commands.clear();
                awaiting_response = false;
                NodeStatus::Failure
            }
            _ => NodeStatus::Running,
        }
    }))
}

pub fn take_action(client: Rc<RefCell<AiTcpClient>>, resource: String) -> Box<dyn BehaviorNode> {
    let mut awaiting_response = false;

    Box::new(ActionNode::new(move |bb| {
        if !awaiting_response {
            client.borrow().send(format!("Take {resource}"));
            awaiting_response = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Ok) => {
                bb.clear("last_response").ok();
                awaiting_response = false;
                NodeStatus::Success
            }
            Ok(ServerMessage::Ko) => {
                bb.clear("last_response").ok();
                awaiting_response = false;
                NodeStatus::Failure
            }
            Ok(_) => NodeStatus::Running,
            Err(err) => {
                eprintln!("{err}");
                NodeStatus::Failure
            }
        }
    }))
}

pub fn food_seeking_sequence(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        look_action(client.clone()),
        Box::new(ConditionNode::new(|bb| {
            matches!(bb.get::<Option<usize>>("food_target_tile"), Ok(Some(_)))
        })),
        navigate_to_tile_action(client.clone(), "food"),
        take_action(client.clone(), "food".to_string()),
    ]))
}

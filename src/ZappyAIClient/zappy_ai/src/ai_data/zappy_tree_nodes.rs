use crate::ai_data::{ServerMessage, WorldModel, receive_command_response, tile_to_commands};
use crate::config::FOOD_SAFE_THRESHOLD;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{
    ActionNode, BehaviorNode, ConditionNode, NodeStatus, SelectorNode, SequenceNode,
};
use behavior_tree::behavior_tree_decorator::RetryUntilNode;
use rand::RngExt;
use std::cell::RefCell;
use std::rc::Rc;

pub fn random_walk(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
) -> Box<dyn BehaviorNode> {
    Box::new(ActionNode::new(move |bb| {
        println!("====>{}<====", "random walk");
        let roll: f32 = rand::rng().random_range(0.0..1.0);
        let cmd = match roll {
            r if r < 0.6 => "Forward",
            r if r < 0.8 => "Left",
            _ => "Right",
        };
        client.borrow().send(cmd.to_string());
        match receive_command_response(&client, &world, bb) {
            ServerMessage::Ok => NodeStatus::Success,
            _ => NodeStatus::Failure,
        }
    }))
}

pub fn food_threshold_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        println!("Food condition");
        match bb.get::<u32>("food") {
            Ok(food) => {
                return if *food >= FOOD_SAFE_THRESHOLD {
                    println!("Go to next branch: elevate ...");
                    true
                } else {
                    false
                }
            }
            Err(err) => {
                eprintln!("Food condition: {err}");
                false
            }
        }
    }))
}

pub fn look_action(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
) -> Box<dyn BehaviorNode> {
    Box::new(ActionNode::new(move |bb| {
        println!("====>{}<====", "look");
        client.borrow().send("Look".to_string());
        match receive_command_response(&client, &world, bb) {
            ServerMessage::Look(_) => NodeStatus::Success,
            _ => NodeStatus::Failure,
        }
    }))
}

pub fn navigate_to_tile_action(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
    tile_key: &'static str,
) -> Box<dyn BehaviorNode> {
    let mut commands: Vec<String> = Vec::new();

    Box::new(ActionNode::new(move |bb| {
        println!("====>{}<====", "navigate to tile");
        if commands.is_empty() {
            let tile_index = match bb.get::<Option<usize>>(&format!("{}_target_tile", tile_key)) {
                Ok(Some(idx)) => *idx,
                _ => return NodeStatus::Failure,
            };
            commands = tile_to_commands(tile_index);
            if commands.is_empty() {
                return NodeStatus::Success;
            }
        }

        while !commands.is_empty() {
            client.borrow().send(commands[0].clone());
            match receive_command_response(&client, &world, bb) {
                ServerMessage::Ok => {
                    commands.remove(0);
                }
                ServerMessage::Dead => {
                    commands.clear();
                    return NodeStatus::Failure;
                }
                _ => {
                    commands.clear();
                    return NodeStatus::Failure;
                }
            }
        }
        NodeStatus::Success
    }))
}

pub fn take_action(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
    resource: String,
) -> Box<dyn BehaviorNode> {
    Box::new(ActionNode::new(move |bb| {
        println!("====>{}<====", "take");
        client.borrow().send(format!("Take {resource}"));
        match receive_command_response(&client, &world, bb) {
            ServerMessage::Ok => NodeStatus::Success,
            _ => NodeStatus::Failure,
        }
    }))
}

pub fn food_seeking_sequence(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        Box::new(RetryUntilNode::new(
            |bb| matches!(bb.get::<Option<usize>>("food_target_tile"), Ok(Some(_))),
            Box::new(SequenceNode::new(vec![
                look_action(client.clone(), world.clone()),
                random_walk(client.clone(), world.clone()),
            ])),
        )),
        navigate_to_tile_action(client.clone(), world.clone(), "food"),
        take_action(client.clone(), world.clone(), "food".to_string()),
    ]))
}

pub fn survive_branch(
    client: Rc<RefCell<AiTcpClient>>,
    world: Rc<RefCell<WorldModel>>,
) -> Box<dyn BehaviorNode> {
    Box::new(SelectorNode::new(vec![
        food_threshold_condition(),
        // food_seeking_sequence(client.clone(), world.clone()),
    ]))
}

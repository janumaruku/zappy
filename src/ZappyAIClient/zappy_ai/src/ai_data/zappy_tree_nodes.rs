use crate::ai_data::{ServerMessage, tile_to_commands};
use crate::config::{ELEVATION_TABLE, FOOD_SAFE_THRESHOLD, INCANT_WAIT_TIMEOUT_S, STONE_PRIORITIES};
use std::time::Instant;
use ai_tcp_client::AiTcpClient;
use behavior_tree::behavior_tree::{
    ActionNode, BehaviorNode, BlackBoard, ConditionNode, NodeStatus, SelectorNode, SequenceNode,
};
use behavior_tree::decorator_node::RunUntilNode;
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
            println!("[random_walk] sending: {cmd}");
            client.borrow().send(cmd.to_string());
            sent = true;
            return NodeStatus::Running;
        }

        let status = match bb.get::<ServerMessage>("last_response") {
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
            Ok(other) => {
                println!("[random_walk] unexpected response: {} → Running", other.variant_name());
                NodeStatus::Running
            }
            Err(err) => {
                println!("[random_walk] no last_response yet ({err}) → Running");
                NodeStatus::Running
            }
        };
        println!("[random_walk] → {status:?}");
        status
    }))
}

pub fn food_threshold_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| match bb.get::<u32>("food") {
        Ok(food) => {
            let result = *food >= FOOD_SAFE_THRESHOLD;
            println!("[food_threshold] food={food}, threshold={FOOD_SAFE_THRESHOLD} → {result}");
            result
        }
        Err(err) => {
            eprintln!("[food_threshold] blackboard error: {err}");
            false
        }
    }))
}

pub fn inventory_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut sent = false;

    Box::new(ActionNode::new(move |bb| {
        if !sent {
            println!("[inventory] sending: Inventory");
            client.borrow().send("Inventory".to_string());
            sent = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Inventory(_)) => {
                println!("[inventory] received inventory response → Success");
                bb.clear("last_response").ok();
                sent = false;
                NodeStatus::Success
            }
            Ok(other) => {
                println!("[inventory] unexpected response: {} → Running", other.variant_name());
                NodeStatus::Running
            }
            Err(err) => {
                println!("[inventory] no last_response yet ({err}) → Running");
                NodeStatus::Running
            }
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
                if commands.is_empty() {
                    awaiting_response = false;
                    NodeStatus::Success
                } else {
                    client.borrow().send(commands[0].clone());
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

pub fn compute_target_stone(bb: &BlackBoard) -> Option<String> {
    let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
    let idx = (level as usize).saturating_sub(1).min(6);
    let req = &ELEVATION_TABLE[idx];

    let required_for = |name: &str| -> u32 {
        match name {
            "linemate"  => req.linemate,
            "deraumere" => req.deraumere,
            "sibur"     => req.sibur,
            "mendiane"  => req.mendiane,
            "phiras"    => req.phiras,
            "thystame"  => req.thystame,
            _           => 0,
        }
    };

    STONE_PRIORITIES.iter().find_map(|(name, _)| {
        let required = required_for(name);
        let current = bb.get::<u32>(name).map(|v| *v).unwrap_or(0);
        if current < required {
            Some(name.to_string())
        } else {
            None
        }
    })
}

pub fn incantation_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut sent = false;

    Box::new(ActionNode::new(move |bb| {
        if !sent {
            println!("[incantation] sending: Incantation");
            client.borrow().send("Incantation".to_string());
            sent = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::LevelUp(level)) => {
                let level = *level;
                println!("[incantation] level up → {level}");
                bb.set("level", level);
                bb.clear("last_response").ok();
                sent = false;
                NodeStatus::Success
            }
            Ok(ServerMessage::Ko) => {
                println!("[incantation] ko → Failure");
                bb.clear("last_response").ok();
                sent = false;
                NodeStatus::Failure
            }
            Ok(ServerMessage::ElevationUnderway) => {
                println!("[incantation] elevation underway, waiting for level up...");
                NodeStatus::Running
            }
            Ok(other) => {
                println!("[incantation] unexpected response: {} → Running", other.variant_name());
                NodeStatus::Running
            }
            Err(err) => {
                println!("[incantation] no response yet ({err}) → Running");
                NodeStatus::Running
            }
        }
    }))
}

pub fn has_required_stones() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
        let idx = (level as usize).saturating_sub(1).min(6);
        let req = &ELEVATION_TABLE[idx];

        let check = |key: &str, required: u32| -> bool {
            bb.get::<u32>(key).map(|v| *v >= required).unwrap_or(false)
        };

        let result = check("linemate", req.linemate)
            && check("deraumere", req.deraumere)
            && check("sibur", req.sibur)
            && check("mendiane", req.mendiane)
            && check("phiras", req.phiras)
            && check("thystame", req.thystame);

        println!("[has_required_stones] level={level} → {result}");
        result
    }))
}

pub fn enough_teammates_on_tile() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
        let idx = (level as usize).saturating_sub(1).min(6);
        let needed = ELEVATION_TABLE[idx].players.saturating_sub(1);

        let teammates = bb.get::<u32>("teammates_on_tile").map(|v| *v).unwrap_or(0);
        let result = teammates >= needed;

        println!("[enough_teammates] level={level}, teammates={teammates}, needed={needed} → {result}");
        result
    }))
}

pub fn not_enough_teammates_on_tile() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
        let idx = (level as usize).saturating_sub(1).min(6);
        let needed = ELEVATION_TABLE[idx].players.saturating_sub(1);
        let teammates = bb.get::<u32>("teammates_on_tile").map(|v| *v).unwrap_or(0);
        let result = needed > 0 && teammates < needed;
        println!("[not_enough_teammates] level={level}, teammates={teammates}, needed={needed} → {result}");
        result
    }))
}

pub fn broadcast_ready_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut sent = false;

    Box::new(ActionNode::new(move |bb| {
        if !sent {
            let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
            println!("[broadcast_ready] sending: Broadcast LVL{level}_READY");
            client.borrow().send(format!("Broadcast LVL{level}_READY"));
            sent = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Ok) => {
                bb.clear("last_response").ok();
                sent = false;
                NodeStatus::Success
            }
            Ok(_) => NodeStatus::Running,
            Err(_) => NodeStatus::Running,
        }
    }))
}

pub fn wait_for_teammates_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut start_time: Option<Instant> = None;
    let mut awaiting_response = false;

    Box::new(ActionNode::new(move |bb| {
        let now = Instant::now();

        if start_time.is_none() {
            start_time = Some(now);
        }

        let elapsed = now.duration_since(start_time.unwrap()).as_secs_f32();
        if elapsed >= INCANT_WAIT_TIMEOUT_S {
            println!("[wait_teammates] timeout after {elapsed:.1}s → Failure");
            start_time = None;
            awaiting_response = false;
            return NodeStatus::Failure;
        }

        if !awaiting_response {
            client.borrow().send("Inventory".to_string());
            awaiting_response = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Inventory(_)) => {
                bb.clear("last_response").ok();
                awaiting_response = false;
                client.borrow().send("Inventory".to_string());
                awaiting_response = true;
                NodeStatus::Running
            }
            Ok(_) => NodeStatus::Running,
            Err(_) => NodeStatus::Running,
        }
    }))
}

pub fn wait_for_teammates_sequence(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        has_required_stones(),
        not_enough_teammates_on_tile(),
        broadcast_ready_action(client.clone()),
        wait_for_teammates_action(client.clone()),
    ]))
}

pub fn stone_navigate_take_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut stone: Option<String> = None;
    let mut commands: Vec<String> = Vec::new();
    let mut awaiting_response = false;
    let mut taking = false;

    Box::new(ActionNode::new(move |bb| {
        // Init
        if stone.is_none() && !awaiting_response && !taking {
            let target = match compute_target_stone(bb) {
                Some(s) => s,
                None => return NodeStatus::Failure,
            };
            let tile_index = match bb.get::<Option<usize>>(&format!("{}_target_tile", target)) {
                Ok(Some(idx)) => *idx,
                _ => return NodeStatus::Failure,
            };
            commands = tile_to_commands(tile_index);
            stone = Some(target);
            if commands.is_empty() {
                taking = true;
            }
        }

        let stone_name = match &stone {
            Some(s) => s.clone(),
            None => return NodeStatus::Failure,
        };

        // Navigation
        if !taking {
            if !awaiting_response {
                client.borrow().send(commands[0].clone());
                awaiting_response = true;
                return NodeStatus::Running;
            }
            match bb.get::<ServerMessage>("last_response") {
                Ok(ServerMessage::Ok) => {
                    bb.clear("last_response").ok();
                    commands.remove(0);
                    if commands.is_empty() {
                        awaiting_response = false;
                        taking = true;
                        // fall through to Take block below
                    } else {
                        client.borrow().send(commands[0].clone());
                        return NodeStatus::Running;
                    }
                }
                Ok(ServerMessage::Ko) => {
                    bb.clear("last_response").ok();
                    commands.clear();
                    stone = None;
                    awaiting_response = false;
                    return NodeStatus::Failure;
                }
                _ => return NodeStatus::Running,
            }
        }

        // Take
        if !awaiting_response {
            println!("[stone_seek] taking {stone_name}");
            client.borrow().send(format!("Take {stone_name}"));
            awaiting_response = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Ok) => {
                bb.clear("last_response").ok();
                stone = None;
                awaiting_response = false;
                taking = false;
                NodeStatus::Success
            }
            Ok(ServerMessage::Ko) => {
                bb.clear("last_response").ok();
                stone = None;
                awaiting_response = false;
                taking = false;
                NodeStatus::Failure
            }
            _ => NodeStatus::Running,
        }
    }))
}

pub fn stone_seeking_sequence(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        inventory_action(client.clone()),
        look_action(client.clone()),
        Box::new(SelectorNode::new(vec![
            stone_navigate_take_action(client.clone()),
            random_walk(client.clone()),
        ])),
    ]))
}

pub fn food_seeking_sequence(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        Box::new(ActionNode::new(|bb| {
            bb.set("food_target_tile", None::<usize>);
            println!("[food_seeking] cleared stale food_target_tile");
            NodeStatus::Success
        })),
        Box::new(RunUntilNode::new(
            |bb| {
                let tile = bb.get::<Option<usize>>("food_target_tile").ok().and_then(|t| *t);
                println!("[food_seeking] food_target_tile={tile:?}");
                tile.is_some()
            },
            Box::new(SequenceNode::new(vec![
                random_walk(client.clone()),
                look_action(client.clone()),
            ])),
        )),
        navigate_to_tile_action(client.clone(), "food"),
        take_action(client.clone(), "food".to_string()),
    ]))
}

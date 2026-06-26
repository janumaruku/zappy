use crate::ai_data::{ServerMessage, tile_to_commands};
use crate::config::{ELEVATION_TABLE, FOOD_CRITICAL_THRESHOLD, FOOD_SAFE_THRESHOLD, STONE_PRIORITIES};
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
    let mut set_commands: Vec<String> = Vec::new();
    let mut awaiting = false;
    let mut initialized = false;

    Box::new(ActionNode::new(move |bb| {
        if !initialized {
            let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
            let idx = (level as usize).saturating_sub(1).min(6);
            let req = &ELEVATION_TABLE[idx];
            set_commands.clear();
            for _ in 0..req.linemate  { set_commands.push("Set linemate".to_string()); }
            for _ in 0..req.deraumere { set_commands.push("Set deraumere".to_string()); }
            for _ in 0..req.sibur     { set_commands.push("Set sibur".to_string()); }
            for _ in 0..req.mendiane  { set_commands.push("Set mendiane".to_string()); }
            for _ in 0..req.phiras    { set_commands.push("Set phiras".to_string()); }
            for _ in 0..req.thystame  { set_commands.push("Set thystame".to_string()); }
            initialized = true;
            println!("[incantation] stones to set: {:?}", set_commands);
        }

        if !set_commands.is_empty() {
            if !awaiting {
                client.borrow().send(set_commands[0].clone());
                awaiting = true;
                return NodeStatus::Running;
            }
            return match bb.get::<ServerMessage>("last_response") {
                Ok(ServerMessage::Ok) => {
                    bb.clear("last_response").ok();
                    set_commands.remove(0);
                    awaiting = false;
                    NodeStatus::Running
                }
                Ok(ServerMessage::Ko) => {
                    println!("[incantation] set stone ko → Failure");
                    bb.clear("last_response").ok();
                    set_commands.clear();
                    awaiting = false;
                    initialized = false;
                    NodeStatus::Failure
                }
                _ => NodeStatus::Running,
            };
        }

        if !awaiting {
            println!("[incantation] sending: Incantation");
            client.borrow().send("Incantation".to_string());
            awaiting = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::LevelUp(level)) => {
                let level = *level;
                println!("[incantation] level up → {level}");
                bb.set("level", level);
                bb.clear("last_response").ok();
                awaiting = false;
                initialized = false;
                NodeStatus::Success
            }
            Ok(ServerMessage::Ko) => {
                println!("[incantation] ko → Failure");
                bb.clear("last_response").ok();
                awaiting = false;
                initialized = false;
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

pub fn food_not_critical_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| match bb.get::<u32>("food") {
        Ok(food) => {
            let result = *food >= FOOD_CRITICAL_THRESHOLD;
            println!("[food_not_critical] food={food}, threshold={FOOD_CRITICAL_THRESHOLD} → {result}");
            result
        }
        Err(_) => false,
    }))
}

pub fn no_broadcast_for_my_level_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let our_level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
        match bb.get::<Option<u8>>("broadcast_level") {
            Ok(Some(lvl)) => {
                let result = *lvl != our_level;
                println!("[no_broadcast_for_my_level] broadcast={lvl}, ours={our_level} → {result}");
                result
            }
            _ => {
                println!("[no_broadcast_for_my_level] no broadcast for my level → true");
                true
            }
        }
    }))
}

pub fn broadcast_received_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let result = bb.get::<u8>("broadcast_k").is_ok();
        println!("[broadcast_received] → {result}");
        result
    }))
}

pub fn broadcast_level_matches() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let our_level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
        match bb.get::<Option<u8>>("broadcast_level") {
            Ok(Some(lvl)) => {
                let result = *lvl == our_level;
                println!("[broadcast_level_matches] broadcast={lvl}, ours={our_level} → {result}");
                result
            }
            _ => {
                println!("[broadcast_level_matches] no broadcast level → false");
                false
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

pub fn wait_for_teammates_sequence(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        has_required_stones(),
        not_enough_teammates_on_tile(),
        no_broadcast_for_my_level_condition(),
        Box::new(RunUntilNode::new(
            |bb| {
                let level = bb.get::<u8>("level").map(|l| *l).unwrap_or(1);
                let idx = (level as usize).saturating_sub(1).min(6);
                let needed = ELEVATION_TABLE[idx].players.saturating_sub(1);
                let teammates = bb.get::<u32>("teammates_on_tile").map(|v| *v).unwrap_or(0);
                let result = teammates >= needed;
                println!("[wait_teammates/condition] teammates={teammates}, needed={needed} → {result}");
                result
            },
            Box::new(SequenceNode::new(vec![
                food_not_critical_condition(),
                broadcast_ready_action(client.clone()),
                look_action(client.clone()),
                inventory_action(client.clone()),
            ])),
        )),
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

pub fn incantation_on_tile_condition() -> Box<dyn BehaviorNode> {
    Box::new(ConditionNode::new(|bb| {
        let result = bb.get::<bool>("incantation_on_tile").map(|v| *v).unwrap_or(false);
        println!("[incantation_on_tile] → {result}");
        result
    }))
}

pub fn answer_elevation_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut awaiting_response = false;

    Box::new(ActionNode::new(move |bb| {
        let on_tile = bb.get::<bool>("incantation_on_tile").map(|v| *v).unwrap_or(false);
        if !on_tile {
            awaiting_response = false;
            return NodeStatus::Success;
        }

        if !awaiting_response {
            println!("[answer_elevation] sending Inventory to keep loop alive");
            client.borrow().send("Inventory".to_string());
            awaiting_response = true;
            return NodeStatus::Running;
        }

        match bb.get::<ServerMessage>("last_response") {
            Ok(ServerMessage::Ko) => {
                bb.clear("last_response").ok();
                bb.set("incantation_on_tile", false);
                awaiting_response = false;
                NodeStatus::Failure
            }
            Ok(_) => {
                bb.clear("last_response").ok();
                client.borrow().send("Inventory".to_string());
                NodeStatus::Running
            }
            Err(_) => NodeStatus::Running,
        }
    }))
}

pub fn answer_elevation_sequence(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    Box::new(SequenceNode::new(vec![
        incantation_on_tile_condition(),
        answer_elevation_action(client),
    ]))
}

fn k_to_commands(k: u8) -> Vec<String> {
    match k {
        1 => vec!["Forward".to_string()],
        2 => vec!["Forward".to_string(), "Left".to_string(), "Forward".to_string()],
        3 => vec!["Left".to_string(), "Forward".to_string()],
        4 => vec!["Left".to_string(), "Forward".to_string(), "Left".to_string(), "Forward".to_string()],
        5 => vec!["Right".to_string(), "Right".to_string(), "Forward".to_string()],
        6 => vec!["Right".to_string(), "Forward".to_string(), "Right".to_string(), "Forward".to_string()],
        7 => vec!["Right".to_string(), "Forward".to_string()],
        8 => vec!["Forward".to_string(), "Right".to_string(), "Forward".to_string()],
        _ => vec![],
    }
}

pub fn navigate_toward_k_action(client: Rc<RefCell<AiTcpClient>>) -> Box<dyn BehaviorNode> {
    let mut commands: Vec<String> = Vec::new();
    let mut awaiting_response = false;
    let mut initialized = false;

    Box::new(ActionNode::new(move |bb| {
        if !initialized {
            let k = match bb.get::<u8>("broadcast_k") {
                Ok(k) => *k,
                Err(_) => {
                    println!("[navigate_k] no broadcast_k → Failure");
                    return NodeStatus::Failure;
                }
            };
            bb.clear("broadcast_k").ok();
            bb.clear("broadcast_level").ok();
            bb.clear("broadcast_timestamp").ok();
            bb.clear("broadcast_text").ok();
            commands = k_to_commands(k);
            initialized = true;
            println!("[navigate_k] k={k}, commands={commands:?}");
        }

        // Navigation mode
        if !commands.is_empty() {
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
                    if !commands.is_empty() {
                        client.borrow().send(commands[0].clone());
                        awaiting_response = true;
                        return NodeStatus::Running;
                    }
                    bb.clear("broadcast_k").ok();
                    bb.clear("broadcast_level").ok();
                    bb.clear("broadcast_timestamp").ok();
                    bb.clear("broadcast_text").ok();
                }
                Ok(ServerMessage::Ko) => {
                    bb.clear("last_response").ok();
                    commands.clear();
                    awaiting_response = false;
                    initialized = false;
                    return NodeStatus::Failure;
                }
                _ => return NodeStatus::Running,
            }
        }

        // On-tile waiting mode (commands exhausted or K=0 at init)
        if bb.get::<bool>("incantation_on_tile").map(|v| *v).unwrap_or(false) {
            awaiting_response = false;
            initialized = false;
            return NodeStatus::Success;
        }

        let food = bb.get::<u32>("food").map(|v| *v).unwrap_or(0);
        if food < FOOD_CRITICAL_THRESHOLD {
            awaiting_response = false;
            initialized = false;
            return NodeStatus::Failure;
        }

        if let Ok(new_k) = bb.get::<u8>("broadcast_k").map(|k| *k) {
            bb.clear("broadcast_k").ok();
            bb.clear("broadcast_level").ok();
            bb.clear("broadcast_timestamp").ok();
            bb.clear("broadcast_text").ok();
            commands = k_to_commands(new_k);
            awaiting_response = false;
            println!("[navigate_k] updated k={new_k}, commands={commands:?}");
            if !commands.is_empty() {
                client.borrow().send(commands[0].clone());
                awaiting_response = true;
                return NodeStatus::Running;
            }
        }

        if awaiting_response {
            match bb.get::<ServerMessage>("last_response") {
                Ok(_) => {
                    bb.clear("last_response").ok();
                    awaiting_response = false;
                }
                Err(_) => return NodeStatus::Running,
            }
        }

        println!("[navigate_k] on broadcaster tile, waiting for incantation");
        client.borrow().send("Inventory".to_string());
        awaiting_response = true;
        NodeStatus::Running
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

use crate::ai_data::ServerMessage;
use behavior_tree::behavior_tree::BlackBoard;
use std::collections::HashMap;

#[derive(Eq, Hash, PartialEq, Clone)]
pub enum Resource {
    Food,
    Linemate,
    Deraumere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame,
    Unknown(String),
}

#[derive(Clone)]
pub enum Orientation {
    Up,
    Right,
    Down,
    Left,
    Unknown(u8),
}

pub struct WorldModel {
    level: u8,
    food: u32,
    inventory: HashMap<Resource, u32>,
    map_width: u32,
    map_height: u32,
}

impl Resource {
    pub fn from(str: &str) -> Self {
        match str {
            "food" => Resource::Food,
            "linemate" => Resource::Linemate,
            "deraumere" => Resource::Deraumere,
            "sibur" => Resource::Sibur,
            "mendiane" => Resource::Mendiane,
            "phiras" => Resource::Phiras,
            "thystame" => Resource::Thystame,
            s => Resource::Unknown(s.to_string()),
        }
    }
}

impl Orientation {
    pub fn from(num: u8) -> Self {
        match num {
            0 => Orientation::Up,
            1 => Orientation::Right,
            2 => Orientation::Down,
            3 => Orientation::Left,
            n => Orientation::Unknown(n),
        }
    }
}

impl WorldModel {
    pub fn new() -> Self {
        WorldModel {
            level: 1,
            food: 0,
            inventory: HashMap::from([
                (Resource::Linemate, 0),
                (Resource::Deraumere, 0),
                (Resource::Sibur, 0),
                (Resource::Mendiane, 0),
                (Resource::Phiras, 0),
                (Resource::Thystame, 0),
            ]),
            map_width: 0,
            map_height: 0,
        }
    }

    pub fn update(&mut self, response: &ServerMessage, blackboard: &mut BlackBoard) {
        match response {
            ServerMessage::Inventory(inventory) => self.update_inventory(inventory, blackboard),
            _ => return,
        }
        blackboard.set("last_response", response.clone());
    }

    fn update_inventory(
        &mut self,
        inventory: &HashMap<Resource, u32>,
        blackboard: &mut BlackBoard,
    ) {
        self.food = *inventory.get(&Resource::Food).unwrap_or(&0);

        self.inventory = inventory
            .iter()
            .filter(|(res, _)| **res != Resource::Food)
            .map(|(res, count)| (res.clone(), *count))
            .collect();

        blackboard.set("food", self.food);
        for (res, count) in &self.inventory {
            if let Some(key) = resource_blackboard_key(res) {
                blackboard.set(key, *count);
            }
        }
    }
}

pub fn resource_blackboard_key(resource: &Resource) -> Option<&'static str> {
    match resource {
        Resource::Linemate => Some("linemate"),
        Resource::Deraumere => Some("deraumere"),
        Resource::Sibur => Some("sibur"),
        Resource::Mendiane => Some("mendiane"),
        Resource::Phiras => Some("phiras"),
        Resource::Thystame => Some("thystame"),
        _ => None,
    }
}

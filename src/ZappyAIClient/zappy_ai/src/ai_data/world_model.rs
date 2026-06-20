use behavior_tree::behavior_tree::BlackBoard;
use std::collections::HashMap;
use crate::ai_data::ServerMessage;

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
    map_with: u32,
    map_height: u32,
}

impl Resource {
    pub fn from(str: &str) -> Self {
        match str {
            "food" => Resource::Food,
            "linemate" => Resource::Food,
            "deraumere" => Resource::Food,
            "sibur" => Resource::Food,
            "mendiane" => Resource::Food,
            "phiras" => Resource::Food,
            "thystame" => Resource::Food,
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
            map_with: 0,
            map_height: 0,
        }
    }

    pub fn update(&mut self, response: &ServerMessage, blackboard: &mut BlackBoard) {
        blackboard.set("last_response", response.clone());
    }
}

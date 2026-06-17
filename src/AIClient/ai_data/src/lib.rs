use std::collections::HashMap;
use behavior_tree::behavior_tree::BlackBoard;

#[derive(Eq, Hash, PartialEq)]
pub enum Resource {
    Linemate,
    Deraumere,
    Sibur,
    Mendiane,
    Phiras,
    Thystame,
}

pub struct WorldModel {
    level: u8,
    food: u32,
    inventory: HashMap<Resource, u32>,
    map_with: u32,
    map_height: u32,
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

    pub fn update(&mut self, response: &str, blackboard: &mut BlackBoard) {
        blackboard.set("last_response", String::from(response));
    }
}

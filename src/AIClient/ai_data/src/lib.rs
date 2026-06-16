use std::collections::HashMap;

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

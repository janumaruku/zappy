use crate::ai_data::ServerMessage;
use behavior_tree::behavior_tree::BlackBoard;
use std::cmp::Ordering;
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

#[derive(Eq, Hash, PartialEq, Clone)]
pub enum TileObject {
    Resource(Resource),
    Player,
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
    visible_tiles: Vec<Vec<TileObject>>,
}

const STONES: [Resource; 7] = [
    Resource::Food,
    Resource::Linemate,
    Resource::Deraumere,
    Resource::Sibur,
    Resource::Mendiane,
    Resource::Phiras,
    Resource::Thystame,
];

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

impl TileObject {
    pub fn from(str: &str) -> Self {
        match str {
            "player" => TileObject::Player,
            str => {
                let result = Resource::from(str);

                match result {
                    Resource::Unknown(line) => TileObject::Unknown(line),
                    other => TileObject::Resource(other),
                }
            }
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
    pub fn new(width: u32, height: u32) -> Self {
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
            map_width: width,
            map_height: height,
            visible_tiles: Vec::new(),
        }
    }

    pub fn update(&mut self, response: &ServerMessage, blackboard: &mut BlackBoard) {
        println!("[world] update: {}", response.variant_name());
        match response {
            ServerMessage::Inventory(inventory) => self.update_inventory(inventory, blackboard),
            ServerMessage::Look(tiles) => self.update_look(tiles, blackboard),
            ServerMessage::LevelUp(level) => self.update_level_up(*level, blackboard),
            ServerMessage::ElevationUnderway => {
                blackboard.set("incantation_on_tile", true);
                blackboard.set("last_response", ServerMessage::ElevationUnderway);
            }
            ServerMessage::Ok => blackboard.set("last_response", ServerMessage::Ok),
            ServerMessage::Ko => blackboard.set("last_response", ServerMessage::Ko),
            _ => {},
        }
        blackboard.set("last_response", response.clone());
    }

    fn update_inventory(
        &mut self,
        inventory: &HashMap<Resource, u32>,
        blackboard: &mut BlackBoard,
    ) {
        self.food = *inventory.get(&Resource::Food).unwrap_or(&0);
        blackboard.set("last_response", ServerMessage::Inventory(inventory.clone()));

        self.inventory = inventory
            .iter()
            .filter(|(res, _)| **res != Resource::Food)
            .map(|(res, count)| (res.clone(), *count))
            .collect();

        blackboard.set("food", self.food);
        println!("[world/inventory] food={}", self.food);
        for (res, count) in &self.inventory {
            if let Some(key) = resource_blackboard_key(res) {
                blackboard.set(key, *count);
                println!("[world/inventory]   {key}={count}");
            }
        }
    }

    fn update_look(&mut self, tiles: &Vec<Vec<TileObject>>, blackboard: &mut BlackBoard) {
        self.visible_tiles = tiles.clone();
        blackboard.set("last_response", ServerMessage::Look(tiles.clone()));
        println!("[world/look] {} tiles visible", tiles.len());

        for res in &STONES {
            blackboard.set(
                &format!("visible_{}_count", resource_blackboard_key(res).unwrap()),
                tiles.iter().fold(0u32, |acc, tile| {
                    let count = tile.iter().fold(0, |count, obj| {
                        if *obj == TileObject::Resource(res.clone()) {
                            count + 1
                        } else {
                            count
                        }
                    });
                    acc + count
                }),
            )
        }

        let players = tiles
            .get(0)
            .map(|tile| {
                tile.iter().fold(0u32, |acc, count| {
                    if *count == TileObject::Player {
                        acc + 1
                    } else {
                        acc
                    }
                })
            })
            .unwrap_or(0)
            .saturating_sub(1);
        blackboard.set("teammates_on_tile", players);
        println!("[world/look] teammates_on_tile={players}");

        for res in &STONES {
            let target = tiles
                .iter()
                .position(|tile| tile.contains(&TileObject::Resource(res.clone())));
            let key = resource_blackboard_key(res).unwrap();
            println!("[world/look]   {key}_target_tile={target:?}");
            blackboard.set(&format!("{key}_target_tile"), target);
        }
    }

    fn update_level_up(&mut self, level: u8, blackboard: &mut BlackBoard) {
        self.level = level;
        blackboard.set("incantation_on_tile", false);
        blackboard.set("last_response", ServerMessage::LevelUp(level));
        blackboard.set("level", level);
        println!("[world/level_up] level={level}");
    }
}

pub fn resource_blackboard_key(resource: &Resource) -> Option<&'static str> {
    match resource {
        Resource::Food => Some("food"),
        Resource::Linemate => Some("linemate"),
        Resource::Deraumere => Some("deraumere"),
        Resource::Sibur => Some("sibur"),
        Resource::Mendiane => Some("mendiane"),
        Resource::Phiras => Some("phiras"),
        Resource::Thystame => Some("thystame"),
        _ => None,
    }
}

pub fn find_row_and_col(tile_index: usize) -> (usize, i32) {
    if tile_index == 0 {
        return (0, 0);
    }

    let mut prev_tt = 0usize;
    let mut level = 1usize;
    loop {
        let tt = prev_tt + 2usize * level + 1;
        if (tile_index <= tt) {
            let center = prev_tt + level + 1;
            return (level, tile_index as i32 - center as i32);
        }

        prev_tt = tt;
        level += 1;
    }
}

pub fn tile_to_commands(tile_index: usize) -> Vec<String> {
    if tile_index == 0 {
        return vec![];
    }

    let mut commands = Vec::new();
    let (row, col) = find_row_and_col(tile_index);
    match col.cmp(&0) {
        Ordering::Less => {
            commands.push("Left".to_string());
            for _ in 0..col.unsigned_abs() as usize {
                commands.push("Forward".to_string());
            }
            commands.push("Right".to_string());
        }
        Ordering::Equal => {}
        Ordering::Greater => {
            commands.push("Right".to_string());
            for _ in 0..col.unsigned_abs() as usize {
                commands.push("Forward".to_string());
            }
            commands.push("Left".to_string());
        }
    };

    for _ in 0..row {
        commands.push("Forward".to_string());
    }

    commands
}

pub const FOOD_SAFE_THRESHOLD: u32 = 10;
pub const FOOD_CRITICAL_THRESHOLD: u32 = 3;

#[derive(Copy, Clone)]
pub struct ElevationRequirement {
    pub players: u32,
    pub linemate: u32,
    pub deraumere: u32,
    pub sibur: u32,
    pub mendiane: u32,
    pub phiras: u32,
    pub thystame: u32,
}

pub const ELEVATION_TABLE: [ElevationRequirement; 7] = [
    ElevationRequirement { players: 1, linemate: 1, deraumere: 0, sibur: 0, mendiane: 0, phiras: 0, thystame: 0 },
    ElevationRequirement { players: 2, linemate: 1, deraumere: 1, sibur: 1, mendiane: 0, phiras: 0, thystame: 0 },
    ElevationRequirement { players: 2, linemate: 2, deraumere: 0, sibur: 1, mendiane: 0, phiras: 2, thystame: 0 },
    ElevationRequirement { players: 4, linemate: 1, deraumere: 1, sibur: 2, mendiane: 0, phiras: 1, thystame: 0 },
    ElevationRequirement { players: 4, linemate: 1, deraumere: 2, sibur: 1, mendiane: 3, phiras: 0, thystame: 0 },
    ElevationRequirement { players: 6, linemate: 1, deraumere: 2, sibur: 3, mendiane: 0, phiras: 1, thystame: 0 },
    ElevationRequirement { players: 6, linemate: 2, deraumere: 2, sibur: 2, mendiane: 2, phiras: 2, thystame: 1 },
];

pub const INCANT_WAIT_TIMEOUT_S: f32 = 30.0;

pub const STONE_PRIORITIES: [(&str, u32); 6] = [
    ("thystame", 10),
    ("phiras",    8),
    ("mendiane",  7),
    ("sibur",     6),
    ("deraumere", 4),
    ("linemate",  2),
];

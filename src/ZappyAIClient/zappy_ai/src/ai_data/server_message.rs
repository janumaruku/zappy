use crate::ai_data::{Orientation, Resource, TileObject};
use std::collections::HashMap;
use std::num::ParseIntError;

#[derive(Clone)]
pub enum ServerMessage {
    Ok,
    Ko,
    Look(Vec<Vec<TileObject>>),
    Inventory(HashMap<Resource, u32>),
    LevelUp(u8),
    Dead,
    Broadcast(u8, String),
    Eject(Orientation),
    Unknown(String),
}

pub fn classify(line: &str) -> ServerMessage {
    let trimmed = line.trim();
    if trimmed.is_empty() {
        return ServerMessage::Unknown(line.to_string());
    }

    if trimmed.starts_with('[') {
        return parse_bracket_response(trimmed);
    }

    let tokens: Vec<&str> = trimmed.split(' ').collect();
    match tokens[0] {
        "ok" => ServerMessage::Ok,
        "ko" => ServerMessage::Ko,
        "dead" => ServerMessage::Dead,
        "eject:" => parse_eject(&tokens),
        "message" => parse_broadcast(&trimmed),
        "Current" => parse_level_up(&tokens),
        _ => ServerMessage::Unknown(line.to_string()),
    }
}

fn parse_level_up(tokens: &Vec<&str>) -> ServerMessage {
    match tokens[2].parse::<u8>() {
        Ok(level) => ServerMessage::LevelUp(level),
        Err(_) => ServerMessage::Unknown(format!("Current level: {}", tokens[2])),
    }
}

fn parse_broadcast(line: &str) -> ServerMessage {
    let rest = line.trim_start_matches("message ");
    let Some((k_part, text)) = rest.split_once(',') else {
        return ServerMessage::Unknown(line.to_string());
    };

    let Ok(k) = k_part.trim().parse::<u8>() else {
        return ServerMessage::Unknown(line.to_string());
    };

    ServerMessage::Broadcast(k, text.trim().to_string())
}

fn parse_eject(tokens: &Vec<&str>) -> ServerMessage {
    let orientation = Orientation::from(tokens[1].parse::<u8>().unwrap());

    ServerMessage::Eject(orientation)
}

fn parse_bracket_response(line: &str) -> ServerMessage {
    let tokens: Vec<&str> = line
        .trim_start_matches('[')
        .trim_end_matches(']')
        .split(',')
        .collect();

    let is_inventory = tokens
        .first()
        .map(|token| {
            token.starts_with("food ")
                && token
                    .split_whitespace()
                    .nth(1)
                    .map(|count| count.parse::<u32>().is_ok())
                    .unwrap_or(false)
        })
        .unwrap_or(false);

    if is_inventory {
        let map: HashMap<Resource, u32> = tokens
            .iter()
            .map(|token| {
                let parts = token.split_whitespace().collect::<Vec<_>>();
                let resource = Resource::from(parts[0]);
                let count = parts[1].parse::<u32>().unwrap();
                (resource, count)
            })
            .collect();

        return ServerMessage::Inventory(map);
    }

    ServerMessage::Look(
        tokens
            .iter()
            .map(|token| {
                token
                    .split_whitespace()
                    .map(|obj| TileObject::from(obj))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>(),
    )
}

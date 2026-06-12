use std::fmt::{Debug, Display, Formatter};

#[derive(Debug)]
pub enum CommandError {
    MissingArgument(String),
    MissingOption(String),
    MissingFlag(String),
    MissingOptionValue(String),
    UnknownToken(String),
    UnknownArgument(String),
}

impl Display for CommandError {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        match self {
            CommandError::MissingArgument(name) => write!(
                f,
                "{}Error: {}Missing required argument {}",
                useful::color::RED,
                useful::color::RESET,
                useful::color::RED.to_string() + name + &useful::color::RESET,
            ),
            CommandError::MissingOption(name) => write!(
                f,
                "{}Error: {}Missing required option {}",
                useful::color::RED,
                useful::color::RESET,
                useful::color::RED.to_string() + name + &useful::color::RESET,
            ),
            CommandError::MissingFlag(name) => write!(
                f,
                "{}Error: {}Missing required flag {}",
                useful::color::RED,
                useful::color::RESET,
                useful::color::RED.to_string() + name + &useful::color::RESET,
            ),
            CommandError::MissingOptionValue(name) => write!(
                f,
                "{}Error: {}Missing value for option {}",
                useful::color::RED,
                useful::color::RESET,
                useful::color::RED.to_string() + name + &useful::color::RESET,
            ),
            CommandError::UnknownToken(token) => write!(
                f,
                "{}Error: {}Unknown option or flag: {}",
                useful::color::RED,
                useful::color::RESET,
                useful::color::RED.to_string() + token + &useful::color::RESET,
            ),
            CommandError::UnknownArgument(name) => write!(
                f,
                "{}Error: {}Unexpected argument {}{name}{}",
                useful::color::RED,
                useful::color::RESET,
                useful::color::RED.to_string(), &useful::color::RESET,
            ),
        }
    }
}

impl std::error::Error for CommandError {}

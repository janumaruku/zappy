use crate::command::CommandContext;

#[derive(Debug, Default)]
pub struct PositionalArgument {
    pub name: String,
    pub description: String,
    pub default: String,
    pub required: bool,
}

#[derive(Debug, Default)]
pub struct CmdOption {
    pub name: String,
    pub description: String,
    pub alias: Option<char>,
    pub default: String,
    pub required: bool,
}

#[derive(Debug, Default)]
pub struct CmdFlag {
    pub name: String,
    pub description: String,
    pub alias: Option<char>,
    pub required: bool,
}

pub struct CommandDefinition {
    pub name: String,
    pub description: String,
    pub arguments: Vec<PositionalArgument>,
    pub options: Vec<CmdOption>,
    pub flags: Vec<CmdFlag>,

    handler: Box<dyn Fn(&CommandContext)>,
}

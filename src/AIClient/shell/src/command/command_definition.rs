#[derive(Debug, Default)]
pub struct PositionalArgument {
    pub name: String,
    pub description: String,
    pub default: String,
    pub required: bool
}

#[derive(Debug, Default)]
pub struct CmdOption {
    pub name: String,
    pub description: String,
    pub alias: char,
    pub default: String,
    pub required: bool
}

#[derive(Debug, Default)]
pub struct CmdFlag {
    pub name: String,
    pub description: String,
    pub alias: char,
    pub required: bool
}

#[derive(Debug, Default)]
pub struct CommandDefinition {
    pub name: String,
    pub description: String,
    pub arguments: Vec<PositionalArgument>,
    pub options: Vec<CmdOption>,
    pub flags: Vec<CmdFlag>,
}
use crate::command::{
    CmdFlag, CmdFlagBuilder, CmdOption, CmdOptionBuilder, CommandContext, CommandDefinition,
    PositionalArgument, PositionalArgumentBuilder,
};

#[derive(Default)]
pub struct CommandBuilder {
    name: String,
    description: String,
    arguments: Vec<PositionalArgument>,
    options: Vec<CmdOption>,
    flags: Vec<CmdFlag>,
    handler: Option<Box<dyn Fn(&CommandContext)>>,
}

impl CommandBuilder {
    pub fn new() -> Self {
        CommandBuilder::default()
    }

    pub fn name(mut self, name: &str) -> Self {
        self.name = name.to_string();

        self
    }

    pub fn description(mut self, description: &str) -> Self {
        self.description = description.to_string();

        self
    }

    pub fn arg(
        mut self,
        configurator: impl FnOnce(PositionalArgumentBuilder) -> PositionalArgumentBuilder,
    ) -> Self {
        let builder = configurator(PositionalArgumentBuilder::new());

        self.arguments.push(builder.build());

        self
    }

    pub fn option(
        mut self,
        configurator: impl FnOnce(CmdOptionBuilder) -> CmdOptionBuilder,
    ) -> Self {
        let builder = configurator(CmdOptionBuilder::new());

        self.options.push(builder.build());

        self
    }

    pub fn flag(mut self, configurator: impl FnOnce(CmdFlagBuilder) -> CmdFlagBuilder) -> Self {
        let builder = configurator(CmdFlagBuilder::new());

        self.flags.push(builder.build());

        self
    }

    pub fn action(mut self, action: impl Fn(&CommandContext) + 'static) -> Self {
        self.handler = Some(Box::new(action));

        self
    }

    pub fn build(self) -> Result<CommandDefinition, String> {
        match self.handler {
            None => Err(format!("Missing handler for command {}", self.name)),
            Some(handler) => Ok(CommandDefinition {
                name: self.name,
                description: self.description,
                arguments: self.arguments,
                options: self.options,
                flags: self.flags,
                handler,
            }),
        }
    }
}

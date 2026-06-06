use crate::command::PositionalArgument;

#[derive(Default)]
pub struct PositionalArgumentBuilder {
    argument: PositionalArgument,
}

impl PositionalArgumentBuilder {
    pub fn new() -> Self {
        PositionalArgumentBuilder::default()
    }

    pub fn name(mut self, name: &str) -> Self {
        self.argument.name = String::from(name);

        self
    }

    pub fn description(mut self, description: &str) -> Self {
        self.argument.description = String::from(description);

        self
    }

    pub fn default_value(mut self, default: &str) -> Self {
        self.argument.default = String::from(default);

        self
    }

    pub fn required(mut self) -> Self {
        self.argument.required = true;

        self
    }

    pub fn build(self) -> PositionalArgument {
        self.argument
    }
}

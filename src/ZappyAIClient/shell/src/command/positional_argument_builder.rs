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
        self.argument.name = name.to_string();

        self
    }

    pub fn description(mut self, description: &str) -> Self {
        self.argument.description = description.to_string();

        self
    }

    pub fn default_value(mut self, default: &str) -> Self {
        self.argument.default = default.to_string();

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

use crate::command::CmdOption;

#[derive(Default)]
pub struct CmdOptionBuilder {
    option: CmdOption,
}

impl CmdOptionBuilder {
    pub fn new() -> Self {
        CmdOptionBuilder::default()
    }

    pub fn name(mut self, name: &str) -> Self {
        self.option.name = name.to_string();

        self
    }

    pub fn description(mut self, description: &str) -> Self {
        self.option.description = description.to_string();

        self
    }

    pub fn alias(mut self, alias: char) -> Self {
        self.option.alias = alias;

        self
    }

    pub fn required(mut self) -> Self {
        self.option.required = true;

        self
    }

    pub fn default_value(mut self, default_value: &str) -> Self {
        self.option.default = default_value.to_string();

        self
    }

    pub fn build(self) -> CmdOption {
        self.option
    }
}

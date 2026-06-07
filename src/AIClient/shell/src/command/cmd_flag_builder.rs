use crate::command::CmdFlag;

#[derive(Default)]
pub struct CmdFlagBuilder {
    flag: CmdFlag,
}

impl CmdFlagBuilder {
    pub fn new() -> Self {
        CmdFlagBuilder::default()
    }

    pub fn name(mut self, name: &str) -> Self {
        self.flag.name = String::from(name);

        self
    }

    pub fn description(mut self, description: &str) -> Self {
        self.flag.description = String::from(description);

        self
    }

    pub fn alias(mut self, alias: char) -> Self {
        self.flag.alias = Option::from(alias);

        self
    }
    
    pub fn required(mut self) -> Self {
        self.flag.required = true;
        
        self
    }
    
    pub fn build(self) -> CmdFlag {
        self.flag
    }
}

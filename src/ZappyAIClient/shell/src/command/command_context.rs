use std::collections::HashMap;

#[derive(Default)]
pub struct CommandContext {
    args: HashMap<String, String>,
    options: HashMap<String, String>,
    flags: Vec<String>,
}

impl CommandContext {
    pub fn arg(&self, name: &str) -> Option<String> {
        self.args.get(name).cloned()
    }

    pub fn has_arg(&self, name: &str) -> bool {
        self.args.contains_key(name)
    }

    pub fn args_count(&self) -> usize {
        self.args.len()
    }

    pub fn option(&self, name: &str) -> Option<String> {
        self.options.get(name).cloned()
    }

    pub fn has_option(&self, name: &str) -> bool {
        self.options.contains_key(name)
    }

    pub fn options_count(&self) -> usize {
        self.options.len()
    }

    pub fn flag(&self, name: &str) -> bool {
        self.flags.contains(&name.to_string())
    }
    
    pub fn flags_count(&self) -> usize {
        self.flags.len()
    }

    pub fn add_arg(&mut self, name: &str, value: &str) {
        self.args.insert(name.to_string(), value.to_string());
    }

    pub fn add_option(&mut self, name: &str, value: &str) {
        self.options.insert(name.to_string(), value.to_string());
    }

    pub fn add_flag(&mut self, name: &str) {
        self.flags.push(name.to_string());
    }
}

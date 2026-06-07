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

    pub(crate) handler: Box<dyn Fn(&CommandContext)>,
}

impl CommandDefinition {
    pub fn has_option(&self, name: &str) -> Option<&CmdOption> {
        self.options.iter().find(|&option| option.name == name)
    }

    pub fn has_flag(&self, name: &str) -> Option<&CmdFlag> {
        self.flags.iter().find(|&flag| flag.name == name)
    }

    fn process_options(
        &self,
        context: &mut CommandContext,
        tokens: &mut Vec<String>,
        option: &CmdOption,
    ) -> Result<(), String> {
        if tokens.len() < 2 {
            Err(format!("Missing option {} value", &option.name))
        } else {
            context.add_option(&option.name, &tokens[1]);
            tokens.drain(..2);
            Ok(())
        }
    }

    fn process_token(
        &self,
        context: &mut CommandContext,
        tokens: &mut Vec<String>,
    ) -> Result<(), String> {
        let raw = &tokens[0];
        let token = if raw.starts_with("--") {
            &raw[2..]
        } else if raw.starts_with('-') {
            &raw[1..]
        } else {
            ""
        };
        match token.is_empty() {
            true => {
                let index = context.args_count();
                if index >= self.arguments.len() {
                    Err(format!("Unexpected argument {}", raw))
                } else {
                    context.add_arg(&self.arguments[index].name, raw);
                    tokens.drain(..1);
                    Ok(())
                }
            }
            false => {
                if let Some(flag) = self.has_flag(token) {
                    context.add_flag(&flag.name);
                    tokens.drain(..1);
                    return Ok(());
                }
                if let Some(option) = self.has_option(token) {
                    return self.process_options(context, tokens, option);
                }
                Err(format!("Unknown token: {}", token))
            }
        }
    }

    pub fn build_context(&self, cmd: &[String]) -> Result<CommandContext, String> {
        let mut tokens = cmd[1..].to_vec();
        let mut context: CommandContext = Default::default();

        while !tokens.is_empty() {
            self.process_token(&mut context, &mut tokens)?;
        }

        for arg in &self.arguments {
            if !context.has_arg(&arg.name) && !arg.default.is_empty() {
                context.add_arg(&arg.name, &arg.default);
            }
        }

        for option in &self.options {
            if !context.has_option(&option.name) && !option.default.is_empty() {
                context.add_option(&option.name, &option.default);
            }
        }

        for arg in &self.arguments {
            if arg.required && !context.has_arg(&arg.name) {
                Err(format!("Missing required argument {}", &arg.name))?;
            }
        }

        for option in &self.options {
            if option.required && !context.has_option(&option.name) {
                Err(format!("Missing required option {}", &option.name))?;
            }
        }

        for flag in &self.flags {
            if flag.required && !context.flag(&flag.name) {
                Err(format!("Missing required flag {}", &flag.name))?;
            }
        }

        Ok(context)
    }
}

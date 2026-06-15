use crate::command::CommandDefinition;
use std::cmp::max;
use std::collections::HashMap;

const MAX_WIDTH: usize = 80;
const INDENT: usize = 4;
const COL_GAP: usize = 4;

fn wrap_text(text: &str, start_col: usize) -> String {
    match text.is_empty() {
        true => "\n".to_string(),
        false => {
            let indent = " ".repeat(start_col);
            let words = text.split_whitespace();
            let mut result = String::new();
            let mut len = start_col;
            let mut first = true;

            for word in words {
                if first {
                    result.push_str(&word);
                    len += word.len();
                    first = false;
                } else if len + 1 + word.len() > MAX_WIDTH {
                    result.push_str(&format!("\n{indent}{word}"));
                    len = start_col + word.len();
                } else {
                    result.push_str(&format!(" {word}"));
                    len += 1 + word.len();
                }
            }

            result + "\n"
        }
    }
}

fn format_section(title: &str, entries: &[(String, String)]) -> String {
    match entries.is_empty() {
        true => String::new(),
        false => {
            let mut max_label_length = 0;
            for (label, _) in entries {
                max_label_length = max(max_label_length, label.len());
            }

            let description_start = INDENT + max_label_length + COL_GAP;
            let mut result = format!("\n{title}\n");

            let indent = " ".repeat(INDENT);
            for (label, description) in entries {
                result.push_str(&format!(
                    "{indent}{label:<width$}{}",
                    wrap_text(description, description_start),
                    width = max_label_length + COL_GAP,
                ));
            }

            result
        }
    }
}

fn append_usage(line: &mut String, token: String, indent_size: usize) {
    match line.len() + 1 + token.len() > MAX_WIDTH {
        true => line.push_str(&format!("\n{}{token}", " ".repeat(indent_size))),
        false => line.push_str(&format!(" {token}")),
    }
}

fn build_usage(command: &CommandDefinition) -> String {
    let indent_size = INDENT + command.name.len() + 1;
    let mut usage = format!("{}{}", " ".repeat(INDENT), command.name);

    for arg in &command.arguments {
        append_usage(
            &mut usage,
            if arg.required {
                format!("<{}>", arg.name)
            } else {
                format!("[{}]", arg.name)
            },
            indent_size,
        )
    }

    for option in &command.options {
        let mut token = if option.required {
            "--".to_string()
        } else {
            "[--".to_string()
        };
        token.push_str(&option.name);
        if let Some(alias) = &option.alias {
            token.push_str(&format!(" | -{}", alias))
        }
        if !option.required {
            token.push_str("]");
        }
        token.push_str(&format!(" <{}>", option.name));
        append_usage(&mut usage, token, indent_size);
    }

    for flag in &command.flags {
        append_usage(
            &mut usage,
            format!(
                "[--{}{}]",
                flag.name,
                if let Some(alias) = &flag.alias {
                    format!(" | -{}", alias)
                } else {
                    "".to_string()
                }
            ),
            indent_size,
        )
    }

    usage.push_str(&format!("\n{}{}", " ".repeat(INDENT), command.name));
    append_usage(&mut usage, "--help | -h".to_string(), indent_size);

    usage
}

pub fn format_help(command: &CommandDefinition) -> String {
    let mut result = format!("Usage\n{}\n", build_usage(command));
    let indent = " ".repeat(INDENT);

    if !command.description.is_empty() {
        result.push_str(&format!(
            "\nDescription\n{indent}{}",
            wrap_text(&command.description, INDENT)
        ))
    }

    let arg_entries: Vec<(String, String)> = command
        .arguments
        .iter()
        .map(|arg| (arg.name.clone(), arg.description.clone()))
        .collect();
    result.push_str(&format_section("Argument(s)", &arg_entries));

    let option_entries: Vec<(String, String)> = command
        .options
        .iter()
        .map(|option| {
            (
                format!(
                    "--{}{}",
                    option.name,
                    if let Some(alias) = &option.alias {
                        format!(", -{alias}")
                    } else {
                        String::new()
                    }
                ),
                option.description.clone(),
            )
        })
        .collect();
    result.push_str(&format_section("Option(s)", &option_entries));

    let flag_entries: Vec<(String, String)> = command
        .flags
        .iter()
        .map(|flag| {
            (
                format!(
                    "--{}{}",
                    flag.name,
                    if let Some(alias) = &flag.alias {
                        format!(", -{}", alias)
                    } else {
                        String::new()
                    }
                ),
                flag.description.clone(),
            )
        })
        .collect();
    result.push_str(&format_section("Flag(s)", &flag_entries));

    result
}

pub fn format_command_list(commands: &HashMap<String, CommandDefinition>) -> String {
    let max_name_length = commands.iter().fold(
        0,
        |acc, (name, _)| {
            if name.len() > acc { name.len() } else { acc }
        },
    );
    let description_start = INDENT + max_name_length + COL_GAP;

    commands.iter().fold(
        "Available commands:\n".to_string(),
        |mut acc, (name, command)| {
            acc.push_str(&format!(
                "{}{:<width$}{}",
                " ".repeat(INDENT),
                name,
                wrap_text(&command.description, description_start),
                width = max_name_length + COL_GAP,
            ));
            acc
        },
    )
}

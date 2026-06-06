/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** CommandDefinition
*/

#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

namespace shell::command {
struct PositionalArgument {
    std::string name;
    std::string description;
    std::string defaultValue;
    bool required = false;
};

struct Option {
    std::string name;
    std::string description;
    std::string alias;
    std::string defaultValue;
    bool required = false;
};

struct Flag {
    std::string name;
    std::string description;
    std::string alias;
    bool required = false;
};

struct CommandContext;

using CommandHandler = std::function<void(CommandContext &)>;

struct CommandDefinition {
    std::string name;
    std::string description;
    std::vector<PositionalArgument> arguments;
    std::vector<Option> options;
    std::vector<Flag> flags;
    CommandHandler handler;

    std::optional<Option> hasOption(const std::string &option);

    std::optional<Flag> hasFlag(const std::string &flag);

    CommandContext buildCommandContext(std::vector<std::string> tokens);

    static void processOption(CommandContext &context,
        std::vector<std::string> &tokens, const Option &option);

    void processToken(CommandContext &context,
        std::vector<std::string> &tokens);
};
} // namespace shell::command

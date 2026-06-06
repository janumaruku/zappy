/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** CommandDefinition
*/

#include <algorithm>
#include <ranges>

#include "CommandContext.hpp"
#include "ContextException.hpp"
#include "Options.hpp"

namespace shell::command {
std::optional<Option> CommandDefinition::hasOption(const std::string &option)
{
    const auto itt =
        std::ranges::find_if(options, [&option](const auto &xpOption) {
            return xpOption.name == option || xpOption.alias == option;
        });

    if (itt == options.end())
        return std::nullopt;

    return std::optional{*itt};
}

std::optional<Flag> CommandDefinition::hasFlag(const std::string &flag)
{
    const auto itt = std::ranges::find_if(flags, [&flag](const auto &xpFlag) {
        return xpFlag.name == flag || xpFlag.alias == flag;
    });

    if (itt == flags.end())
        return std::nullopt;

    return std::optional{*itt};
}

CommandContext CommandDefinition::buildCommandContext(
    std::vector<std::string> tokens)
{
    tokens.erase(tokens.begin());
    CommandContext context;

    while (!tokens.empty())
        processToken(context, tokens);

    for (const auto &arg : arguments)
        if (!context.hasArg(arg.name) && !arg.defaultValue.empty())
            context.addArg(arg.name, arg.defaultValue);

    for (const auto &option : options)
        if (!context.hasOption(option.name) && !option.defaultValue.empty())
            context.addOption(option.name, option.defaultValue);

    for (const auto &arg : arguments)
        if (arg.required && !context.hasArg(arg.name))
            throw MissingArgumentException(arg.name);

    for (const auto &option : options)
        if (option.required && !context.hasOption(option.name))
            throw MissingOptionException(option.name);

    for (const auto &flag : flags)
        if (flag.required && !context.flag(flag.name))
            throw MissingFlagException(flag.name);

    return context;
}

void CommandDefinition::processOption(CommandContext &context,
    std::vector<std::string> &tokens, const Option &option)
{
    if (tokens.size() < 2)
        throw MissingOptionValueException(option.name);

    context.addOption(option.name, tokens[1]);
    tokens.erase(tokens.begin(), tokens.begin() + 2);
}

void CommandDefinition::processToken(CommandContext &context,
    std::vector<std::string> &tokens)
{
    const auto &raw  = tokens.front();
    const auto token = [&raw]() -> std::string {
        if (raw.starts_with("--"))
            return raw.substr(2);
        if (raw.starts_with("-"))
            return raw.substr(1);
        return "";
    }();
    if (!token.empty()) {
        if (const auto flag = hasFlag(token); flag) {
            context.addFlag(flag->name);
            tokens.erase(tokens.begin());
            return;
        }
        if (const auto temp = hasOption(token); temp) {
            processOption(context, tokens, *temp);
            return;
        }
        throw UnknownTokenException(token);
    }

    const auto index = context.argCount();

    if (index >= this->arguments.size())
        throw UnexpectedArgumentException(raw);

    context.addArg(this->arguments[index].name, raw);
    tokens.erase(tokens.begin());
}
} // namespace shell::command

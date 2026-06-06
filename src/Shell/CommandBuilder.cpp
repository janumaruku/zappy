/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** CommandBuilder
*/

#include "CommandBuilder.hpp"

namespace shell {
namespace command {
CommandBuilder &CommandBuilder::name(const std::string &name) noexcept
{
    _definition.name = name;

    return *this;
}

CommandBuilder &CommandBuilder::description(
    const std::string &description) noexcept
{
    _definition.description = description;

    return *this;
}

CommandBuilder &CommandBuilder::arg(ArgumentConfigurator configure) noexcept
{
    PositionalArgumentBuilder builder;
    configure(builder);
    _definition.arguments.push_back(builder.build());

    return *this;
}

CommandBuilder &CommandBuilder::option(OptionConfigurator configure) noexcept
{
    OptionBuilder builder;
    configure(builder);
    _definition.options.push_back(builder.build());

    return *this;
}

CommandBuilder &CommandBuilder::flag(FlagConfigurator configure) noexcept
{
    FlagBuilder builder;
    configure(builder);
    _definition.flags.push_back(builder.build());

    return *this;
}

CommandBuilder &CommandBuilder::action(
    const std::function<void(CommandContext &)> &action) noexcept
{
    _definition.handler = action;

    return *this;
}

CommandDefinition CommandBuilder::build() noexcept
{
    return _definition;
}
} // namespace command
} // namespace shell

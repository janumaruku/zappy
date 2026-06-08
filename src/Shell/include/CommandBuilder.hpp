/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** CommandBuilder
*/

#pragma once
#include <string>

#include "CommandDefinition.hpp"
#include "FlagBuilder.hpp"
#include "OptionBuilder.hpp"

namespace shell::command {
using OptionConfigurator = std::function<void(OptionBuilder &)>;
using FlagConfigurator   = std::function<void(FlagBuilder &)>;

class CommandBuilder {
public:
    CommandBuilder &name(const std::string &name) noexcept;

    CommandBuilder &description(const std::string &description) noexcept;

    CommandBuilder &arg(ArgumentConfigurator configure) noexcept;

    CommandBuilder &option(OptionConfigurator configure) noexcept;

    CommandBuilder &flag(FlagConfigurator configure) noexcept;

    CommandBuilder &action(const std::function<void(CommandContext &)> &action)
        noexcept;

    CommandDefinition build() noexcept;

private:
    CommandDefinition _definition;
};
} // namespace shell::command

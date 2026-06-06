/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** PositionalArgumentBuilder
*/

#pragma once
#include <string>

#include "CommandDefinition.hpp"

namespace shell::command {
class PositionalArgumentBuilder {
public:
    PositionalArgumentBuilder &name(const std::string &name) noexcept;

    PositionalArgumentBuilder &description(const std::string &description)
        noexcept;

    PositionalArgumentBuilder &defaultValue(const std::string &defaultValue)
        noexcept;

    PositionalArgumentBuilder &required() noexcept;

    [[nodiscard]] PositionalArgument build() const noexcept;

private:
    PositionalArgument _argument;
};
} // namespace shell::command

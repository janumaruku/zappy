/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** FlagBuilder
*/

#pragma once
#include <string>

#include "CommandDefinition.hpp"

namespace shell::command {
class FlagBuilder {
public:
    FlagBuilder &name(const std::string &name) noexcept;

    FlagBuilder &description(const std::string &description) noexcept;

    FlagBuilder &alias(const std::string &alias) noexcept;

    FlagBuilder &required() noexcept;

    [[nodiscard]] Flag build() const noexcept;

private:
    Flag _flag;
};
}

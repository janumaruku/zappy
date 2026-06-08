/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** OptionBuilder
*/

#pragma once
#include <functional>
#include <string>

#include "PositionalArgumentBuilder.hpp"

namespace shell::command {
using ArgumentConfigurator =
    std::function<void(PositionalArgumentBuilder &)>;

class OptionBuilder {
public:
    OptionBuilder &name(const std::string &name) noexcept;

    OptionBuilder &description(const std::string &description) noexcept;

    OptionBuilder &alias(const std::string &alias) noexcept;

    OptionBuilder &required() noexcept;

    OptionBuilder &defaultValue(const std::string &def) noexcept;

    [[nodiscard]] Option build() const noexcept;

private:
    Option _option;
};
}

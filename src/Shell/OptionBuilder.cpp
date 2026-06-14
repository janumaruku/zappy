/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** OptionBuilder
*/

#include "OptionBuilder.hpp"

namespace shell::command {
OptionBuilder &OptionBuilder::name(const std::string &name) noexcept
{
    _option.name = name;

    return *this;
}

OptionBuilder &OptionBuilder::description(
    const std::string &description) noexcept
{
    _option.description = description;

    return *this;
}

OptionBuilder &OptionBuilder::alias(const std::string &alias) noexcept
{
    _option.alias = alias;

    return *this;
}

OptionBuilder &OptionBuilder::required() noexcept
{
    _option.required = true;

    return *this;
}

OptionBuilder & OptionBuilder::defaultValue(const std::string &def) noexcept
{
    _option.defaultValue = def;

    return *this;
}

Option OptionBuilder::build() const noexcept
{
    return _option;
}
}

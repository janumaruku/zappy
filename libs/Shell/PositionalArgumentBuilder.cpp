/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** PositionalArgumentBuilder
*/

#include "PositionalArgumentBuilder.hpp"

namespace shell {
namespace command {
PositionalArgumentBuilder & PositionalArgumentBuilder::name(
    const std::string &name) noexcept
{
    _argument.name = name;

    return *this;
}

PositionalArgumentBuilder & PositionalArgumentBuilder::description(
    const std::string &description) noexcept
{
    _argument.description = description;

    return *this;
}

PositionalArgumentBuilder & PositionalArgumentBuilder::defaultValue(
    const std::string &defaultValue) noexcept
{
    _argument.defaultValue = defaultValue;

    return *this;
}

PositionalArgumentBuilder & PositionalArgumentBuilder::required() noexcept
{
    _argument.required = true;

    return *this;
}

PositionalArgument PositionalArgumentBuilder::build() const noexcept
{
    return _argument;
}
} // namespace command
} // namespace shell

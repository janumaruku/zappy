/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** XOptionBuilder
*/

#include "XOptionBuilder.hpp"

namespace shell::command {
XOptionBuilder & XOptionBuilder::name(const std::string &name) noexcept
{
    _option.name = name;

    return *this;
}

XOptionBuilder & XOptionBuilder::description(
    const std::string &description) noexcept
{
    _option.description = description;

    return *this;
}

XOptionBuilder & XOptionBuilder::alias(const std::string &alias) noexcept
{
    _option.alias = alias;

    return *this;
}

XOptionBuilder & XOptionBuilder::min(const std::size_t &min) noexcept
{
    _option.min = min;

    return *this;
}

XOptionBuilder & XOptionBuilder::required() noexcept
{
    _option.required = true;

    return *this;
}

XOption XOptionBuilder::build() const noexcept
{
    return _option;
}
} // command
// shell

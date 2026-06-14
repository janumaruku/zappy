/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** FlagBuilder
*/

#include "FlagBuilder.hpp"

namespace shell::command {
FlagBuilder &FlagBuilder::name(const std::string &name) noexcept
{
    _flag.name = name;

    return *this;
}

FlagBuilder &FlagBuilder::description(const std::string &description) noexcept
{
    _flag.description = description;

    return *this;
}

FlagBuilder &FlagBuilder::alias(const std::string &alias) noexcept
{
    _flag.alias = alias;

    return *this;
}

FlagBuilder &FlagBuilder::required() noexcept
{
    _flag.required = true;

    return *this;
}

Flag FlagBuilder::build() const noexcept
{
    return _flag;
}
}

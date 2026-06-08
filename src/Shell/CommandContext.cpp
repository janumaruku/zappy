/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** CommandDefinition
*/

#include "CommandContext.hpp"

#include <stdexcept>

#include "constants.hpp"
#include "StringUtils.hpp"

namespace shell {
std::string command::CommandContext::arg(const std::string &name) const
{
    const auto itt = std::ranges::find_if(_args, [&name](const auto &arg) {
        return arg.first == name;
    });

    if (itt == _args.end())
        throw std::out_of_range{"Argument " + name + " not found"};

    return itt->second;
}

std::size_t command::CommandContext::argCount() const noexcept
{
    return _args.size();
}

bool command::CommandContext::hasArg(const std::string &name) const noexcept
{
    const auto itt = std::ranges::find_if(_args, [&name](const auto &arg) {
        return arg.first == name;
    });

    return itt != _args.end();
}

std::string command::CommandContext::option(const std::string &name) const
{
    if (!hasOption(name))
        throw std::out_of_range{"Option " + name + " not found"};

    return _options.at(name);
}

bool command::CommandContext::hasOption(const std::string &name) const noexcept
{
    return _options.contains(name);
}

bool command::CommandContext::flag(const std::string &name) const noexcept
{
    const auto itt = std::ranges::find(_flags, name);

    return itt != _flags.end();
}

void command::CommandContext::addArg(const std::string &name,
    const std::string &arg) noexcept
{
    _args.emplace_back(name, arg);
}

void command::CommandContext::addOption(const std::string &name,
    const std::string &option) noexcept
{
    _options.emplace(name, option);
}

void command::CommandContext::addFlag(const std::string &name) noexcept
{
    _flags.emplace_back(name);
}
} // namespace shell

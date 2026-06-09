/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** HelpFormatter
*/

#ifndef SHELL_HELP_FORMATTER_HPP
#define SHELL_HELP_FORMATTER_HPP

#include <string>
#include <unordered_map>

#include "CommandDefinition.hpp"

namespace shell {
std::string formatHelp(const command::CommandDefinition &def);

std::string formatCommandList(
    const std::unordered_map<std::string, command::CommandDefinition> &commands);
} // namespace shell

#endif // SHELL_HELP_FORMATTER_HPP

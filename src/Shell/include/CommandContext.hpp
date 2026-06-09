/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** CommandDefinition
*/

#ifndef SHELL_COMMAND_CONTEXT_HPP
#define SHELL_COMMAND_CONTEXT_HPP

#include "CommandDefinition.hpp"

namespace shell::command {
struct CommandContext {
    [[nodiscard]] std::string arg(const std::string &name) const;

    [[nodiscard]] bool hasArg(const std::string &name) const noexcept;

    [[nodiscard]] std::size_t argCount() const noexcept;

    [[nodiscard]] std::string option(const std::string &name) const;

    [[nodiscard]] bool hasOption(const std::string &name) const noexcept;

    [[nodiscard]] std::vector<std::string> xOption(
        const std::string &name) const;

    [[nodiscard]] bool hasXOption(const std::string &name) const noexcept;

    [[nodiscard]] bool flag(const std::string &name) const noexcept;

    void addArg(const std::string &name, const std::string &arg) noexcept;

    void addOption(const std::string &name, const std::string &option) noexcept;

    void addXOption(const std::string &name, const std::string &option) noexcept;

    void addFlag(const std::string &name) noexcept;

private:
    std::vector<std::pair<std::string, std::string>> _args;
    std::unordered_map<std::string, std::string> _options;
    std::unordered_map<std::string, std::vector<std::string>> _xOptions;
    std::vector<std::string> _flags;
};
} // namespace shell::command

#endif // SHELL_COMMAND_CONTEXT_HPP

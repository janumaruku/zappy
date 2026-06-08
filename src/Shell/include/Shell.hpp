/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** Shell
*/

#pragma once
#include <string>

#include "CommandDefinition.hpp"
#include "ShellException.hpp"

namespace shell {
class Shell {
public:
    using Middleware = std::function<void()>;

    Shell();

    ~Shell() = default;

    explicit Shell(const std::string &name);

    explicit Shell(const std::string &name, const std::string &prompt);

    Shell(const Shell &) = delete;

    Shell &operator=(const Shell &) = delete;

    Shell(Shell &&) = delete;

    Shell &operator=(Shell &&) = delete;

    void setMiddleware(Middleware middleware) noexcept;

    void registerCommand(const command::CommandDefinition &definition) noexcept;

    void run();

private:
    std::string _name   = "Default Shell";
    std::string _prompt = "> ";
    std::vector<Middleware> _middleware;
    std::unordered_map<std::string, command::CommandDefinition> _commands;

    void registerBuiltins() noexcept;

    void runMiddlewares() const;

    void executeCommand(const std::vector<std::string> &tokens);
};

std::vector<std::string> split(const std::string &command);

bool isEmptyLine(const std::string &line) noexcept;
} // shell

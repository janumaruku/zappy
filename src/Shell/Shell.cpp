/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** Shell
*/

#include "Shell.hpp"

#include <iostream>
#include <sstream>

#include "CommandBuilder.hpp"
#include "Prompt.hpp"
#include "CommandContext.hpp"
#include "constants.hpp"
#include "ContextException.hpp"
#include "HelpFormatter.hpp"

namespace shell {
Shell::Shell()
{
    registerBuiltins();
}

Shell::Shell(const std::string &name): _name{name}
{
    registerBuiltins();
}

Shell::Shell(const std::string &name, const std::string &prompt): _name{name},
    _prompt{prompt}
{
    registerBuiltins();
}

void Shell::registerBuiltins() noexcept
{
    auto exitCmd = command::CommandBuilder{}
        .name("exit")
        .description("Exit the shell")
        .action([](auto &) {
            throw ShellExitException{};
        })
        .build();

    _commands.emplace(exitCmd.name, exitCmd);

    auto helpCmd = command::CommandBuilder{}
        .name("help")
        .description("Display help for a command")
        .arg([](command::PositionalArgumentBuilder &b) {
            b.name("command").description("Command to get help for");
        })
        .action([this](auto &ctx) {
            if (!ctx.hasArg("command")) {
                std::cout << formatCommandList(_commands);
                return;
            }
            const auto &cmdName = ctx.arg("command");
            const auto itt = _commands.find(cmdName);
            if (itt == _commands.end()) {
                std::cerr << _name << ": help: unknown command: "
                          << utils::RED << cmdName << utils::RESET << std::endl;
                return;
            }
            std::cout << formatHelp(itt->second);
        })
        .build();

    _commands.emplace(helpCmd.name, helpCmd);
}

void Shell::setMiddleware(Middleware middleware) noexcept
{
    _middleware.emplace_back(middleware);
}

void Shell::registerCommand(const command::CommandDefinition &definition)
    noexcept
{
    _commands.emplace(definition.name, definition);
}

void Shell::run()
{
    Prompt prompt{_prompt, [this]() { runMiddlewares(); }};

    while (true) {
        auto line = prompt.getline();
        if (!line)
            return;
        if (isEmptyLine(*line))
            continue;
        runMiddlewares();
        try {
            executeCommand(split(*line));
        } catch (const ShellExitException &) {
            return;
        } catch (const std::exception &) {}
    }
}

void Shell::runMiddlewares() const
{
    for (auto &middleware: _middleware) {
        middleware();
    }
}

void Shell::executeCommand(const std::vector<std::string> &tokens)
{
    const auto itt = _commands.find(tokens.front());
    if (itt == _commands.end()) {
        std::cerr << _name << ": command not found: " << utils::RED << tokens.
            front() << utils::RESET << std::endl;
        return;
    }

    command::CommandDefinition &def = itt->second;
    try {
        command::CommandContext context = def.buildCommandContext(tokens);

        def.handler(context);
    } catch (const command::ContextException &e) {
        std::cerr << e.what() << std::endl;
    } catch (const std::exception &) {
        throw;
    }
}

std::vector<std::string> split(const std::string &command)
{
    std::vector<std::string> result;
    auto isQuote          = false;
    const std::size_t len = command.length();
    std::size_t pos       = 0;

    result.emplace_back();
    for (std::size_t i = 0; i < len; ++i) {
        if (command[i] == '"') {
            isQuote = !isQuote;
            continue;
        }
        if (command[i] == ' ' && !isQuote) {
            result.emplace_back();
            ++pos;
            continue;
        }
        result[pos].push_back(command[i]);
    }

    return result;
}

bool isEmptyLine(const std::string &line) noexcept
{
    std::stringstream sstream{line};
    std::string temp;

    return !(sstream >> temp);
}
} // shell

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#include <sstream>
#include "include/Commands.hpp"
#include "include/ProtocolHandler.hpp"

ProtocolHandler::ProtocolHandler() noexcept
{
    registerCommand("msz", []() { return new MszCommand(); });
    registerCommand("bct", []() { return new BctCommand(); });
    registerCommand("mct", []() { return new MctCommand(); });
    registerCommand("tna", []() { return new TnaCommand(); });
    registerCommand("ppo", []() { return new PpoCommand(); });
    registerCommand("plv", []() { return new PlvCommand(); });
    registerCommand("pin", []() { return new PinCommand(); });
    registerCommand("sgt", []() { return new SgtCommand(); });
    registerCommand("sst", []() { return new SstCommand(); });

}

void ProtocolHandler::handleLine(const std::string line) noexcept
{
    std::istringstream iss(line);
    std::string command;
    std::string args;

    iss >> command;
    std::getline(iss, args);

    auto it = _factories.find(command);
    if (it != _factories.end()) {
        std::unique_ptr<ICommand> cmd = it->second();
        cmd->execute(_worldState, args);
        delete cmd;
    }
}

void ProtocolHandler::registerCommand(const std::string &name,
    std::function<ICommand*()> creator) noexcept
{
    _factories[name] = creator;
}

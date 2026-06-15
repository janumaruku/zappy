/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#include <sstream>
#include "include/Commands.hpp"
#include "include/ProtocolHandler.hpp"

#include <iostream>

namespace zappy::gui {

ProtocolHandler::ProtocolHandler(WorldState &worldState) noexcept : _worldState(
    worldState)
{
    registerCommand();
}


void ProtocolHandler::handleLine(const std::string& line) noexcept
{
    try {
        std::vector<std::string> args;
        std::istringstream iss(line);
        std::string command;

        while (iss >> command)
            args.push_back(command);

        // _factory.create(args[0], _worldState, args)->execute(_worldState, args);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


void ProtocolHandler::registerCommand(
    ) noexcept
{
    _factory.registerCreator<MszCommand>("msz");
}
}

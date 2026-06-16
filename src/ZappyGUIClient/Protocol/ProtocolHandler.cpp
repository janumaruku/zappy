/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "StringUtils.hpp"
#include "ProtocolHandler.hpp"
#include "BctCommand.hpp"
#include "MctCommand.hpp"
#include "MszCommand.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

ProtocolHandler::ProtocolHandler(WorldState &w) noexcept : _worldState(w)
{
    registerCommands();
}

void ProtocolHandler::registerCommands() noexcept
{
    _factory.registerCreator<BctCommand>("bct");
    _factory.registerCreator<MctCommand>("mct");
    _factory.registerCreator<MszCommand>("msz");
}

void ProtocolHandler::handleLine(const std::string& line) noexcept
{
    auto cmd = utils::StringUtils::split(line);
    
    try {
        auto toExec = _factory.create(cmd[0]);
        toExec->execute(_worldState, cmd);
    } catch (const std::exception &e) {
        std::cerr << "ko\n";
        std::cerr.flush();
    }
}

}

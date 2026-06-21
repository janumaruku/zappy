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
#include "EboCommand.hpp"
#include "EdiCommand.hpp"
#include "PnwCommand.hpp"
#include "PpoCommand.hpp"
#include "StringUtils.hpp"
#include "ProtocolHandler.hpp"
#include "BctCommand.hpp"
#include "MctCommand.hpp"
#include "MszCommand.hpp"
#include "EnwCommand.hpp"
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
    _factory.registerCreator<PnwCommand>("pnw");
    _factory.registerCreator<PpoCommand>("ppo");
    _factory.registerCreator<EnwCommand>("enw");
    _factory.registerCreator<EboCommand>("ebo");
    _factory.registerCreator<EdiCommand>("edi");
}

void ProtocolHandler::handleLine(const std::string& line) noexcept
{
    auto cmd = utils::StringUtils::split(line);
    
    try {
        auto name = cmd[0];
        cmd.erase(cmd.begin());
        auto toExec = _factory.create(name);
        toExec->execute(_worldState, cmd);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr.flush();
    }
}

}

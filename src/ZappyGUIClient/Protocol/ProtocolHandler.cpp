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
#include "Commands/include/BctCommand.hpp"
#include "Commands/include/MctCommand.hpp"
#include "Commands/include/MszCommand.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

ProtocolHandler::ProtocolHandler(WorldState &w) noexcept : _worldState(w)
{
    registerCommand<BctCommand<WorldState &, std::vector<std::string>>>("bct");
    registerCommand<MctCommand<WorldState &, std::vector<std::string>>>("mct");
    registerCommand<MszCommand<WorldState &, std::vector<std::string>>>("msz");
}

void ProtocolHandler::handleLine(const std::string& line) noexcept
{
    auto cmd = utils::StringUtils::split(line);
    auto toExec = _factory.create(cmd[0]);

    try {
        toExec->execute(_worldState, cmd);
    } catch (const std::exception &e) {
        std::cerr << "ko\n";
        std::cerr.flush();
    }
}

}

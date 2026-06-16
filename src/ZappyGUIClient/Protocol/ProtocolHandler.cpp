/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#include <sstream>
#include <iostream>
#include "Commands.hpp"
#include "StringUtils.hpp"
#include "include/Commands.hpp"
#include "include/ProtocolHandler.hpp"
#include "BctCommand.hpp"
#include "MctCommand.hpp"
#include "MszCommand.hpp"

namespace zappy::gui {

ProtocolHandler::ProtocolHandler() noexcept
{
    _registerCommand<BctCommand>();
    _registerCommand<MctCommand>();
    _registerCommand<MszCommand>();
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

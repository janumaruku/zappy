/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#include <sstream>
#include "StringUtils.hpp"
#include "include/Commands.hpp"
#include "include/ProtocolHandler.hpp"

#include <iostream>

namespace zappy::gui {

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

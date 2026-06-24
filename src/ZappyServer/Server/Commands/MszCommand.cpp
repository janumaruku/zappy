/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MszCommand.cpp
*/

#include "MszCommand.hpp"

#include <memory>
#include <string>

#include "GUISession.hpp"
#include "Server.hpp"

namespace zappy::server {

bool MszCommand::execute(GUISession &session, const std::vector<std::string> &)
{
    const auto &map = session.getServer().getMap();

    session.send("msz " + std::to_string(map.getWidth()) + " "
        + std::to_string(map.getHeight()) + "\n");
    return true;
}

bool MszCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> MszCommand::create()
{
    return std::make_unique<MszCommand>();
}

}

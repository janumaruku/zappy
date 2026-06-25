/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SgtCommand.cpp
*/

#include "SgtCommand.hpp"

#include <memory>
#include <string>

#include "GUISession.hpp"
#include "Server.hpp"

namespace zappy::server {

bool SgtCommand::execute(GUISession &session, const std::vector<std::string> &)
{
    session.send("sgt " + std::to_string(session.getServer().getFrequency()) + "\n");
    return true;
}

bool SgtCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> SgtCommand::create()
{
    return std::make_unique<SgtCommand>();
}

}

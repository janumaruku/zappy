/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "BroadcastCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool BroadcastCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool BroadcastCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("Broadcast" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> BroadcastCommand::create()
{
    return std::unique_ptr<BroadcastCommand>(new BroadcastCommand());
}

}
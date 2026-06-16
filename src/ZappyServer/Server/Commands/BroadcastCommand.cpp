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

bool BroadcastCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool BroadcastCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Broadcast" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> BroadcastCommand::create()
{
    return std::make_unique<BroadcastCommand>(BroadcastCommand());
}

}
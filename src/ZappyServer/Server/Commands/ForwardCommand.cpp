/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "ForwardCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ForwardCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool ForwardCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Forward" + zappy::data::PACKET_END);
    return true;
}

}
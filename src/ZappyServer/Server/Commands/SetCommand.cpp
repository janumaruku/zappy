/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "SetCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool SetCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool SetCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Set" + cmd[1] + zappy::data::PACKET_END);
    return true;
}

}
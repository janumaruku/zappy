/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "LeftCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool LeftCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool LeftCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Left" + zappy::data::PACKET_END);
    return true;
}

}
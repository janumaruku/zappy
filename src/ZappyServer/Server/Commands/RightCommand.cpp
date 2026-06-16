/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "RightCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool RightCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool RightCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Right" + zappy::data::PACKET_END);
    return true;
}

}
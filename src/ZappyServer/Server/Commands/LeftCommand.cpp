/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LefCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "LefCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool LefCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool LefCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Lef" + zappy::data::PACKET_END);
    return true;
}

}
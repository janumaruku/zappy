/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "IncantationCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool IncantationCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool IncantationCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Incantation" + zappy::data::PACKET_END);
    return true;
}

}
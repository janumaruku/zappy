/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "EjectCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool EjectCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool EjectCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Eject" + zappy::data::PACKET_END);
    return true;
}

}
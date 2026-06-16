/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "LookCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool LookCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool LookCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Look" + zappy::data::PACKET_END);
    return true;
}

}
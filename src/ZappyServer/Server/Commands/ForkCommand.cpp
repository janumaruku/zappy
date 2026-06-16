/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "ForkCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ForkCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool ForkCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Fork" + zappy::data::PACKET_END);
    return true;
}

}
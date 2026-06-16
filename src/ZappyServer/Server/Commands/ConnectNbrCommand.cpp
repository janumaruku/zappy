/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "ConnectNbrCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ConnectNbrCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool ConnectNbrCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("ConnectNbr" + zappy::data::PACKET_END);
    return true;
}

}
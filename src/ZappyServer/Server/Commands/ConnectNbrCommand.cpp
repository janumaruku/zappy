/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "ConnectNbrCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ConnectNbrCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool ConnectNbrCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("ConnectNbr" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> ConnectNbrCommand::create()
{
    return std::make_unique<ConnectNbrCommand>(ConnectNbrCommand());
}

}
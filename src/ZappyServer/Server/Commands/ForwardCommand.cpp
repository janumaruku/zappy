/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "ForwardCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ForwardCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool ForwardCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("ForwardCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> ForwardCommand::create()
{
    return std::unique_ptr<ForwardCommand>(new ForwardCommand());
}

}
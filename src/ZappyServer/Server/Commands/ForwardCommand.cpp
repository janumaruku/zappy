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

bool ForwardCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool ForwardCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Forward" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> ForwardCommand::create()
{
    return std::make_unique<ForwardCommand>(ForwardCommand());
}

}
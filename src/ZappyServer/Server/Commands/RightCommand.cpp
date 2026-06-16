/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "RightCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool RightCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool RightCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("RightCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> RightCommand::create()
{
    return std::unique_ptr<RightCommand>(new RightCommand());
}

}
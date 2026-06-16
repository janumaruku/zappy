/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "SetCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool SetCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool SetCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("SetCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> SetCommand::create()
{
    return std::unique_ptr<SetCommand>(new SetCommand());
}

}
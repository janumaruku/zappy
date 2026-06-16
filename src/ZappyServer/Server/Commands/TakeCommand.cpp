/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "TakeCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool TakeCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool TakeCommand::execute(const std::vector<std::string> &cmd, AISession &session)
{
    session.send("Take" + cmd[0] + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> TakeCommand::create()
{
    return std::make_unique<TakeCommand>(TakeCommand());
}

}
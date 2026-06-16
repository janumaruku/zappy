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

bool TakeCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool TakeCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("TakeCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> TakeCommand::create()
{
    return std::unique_ptr<TakeCommand>(new TakeCommand());
}

}
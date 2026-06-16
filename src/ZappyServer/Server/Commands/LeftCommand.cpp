/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "LeftCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool LeftCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool LeftCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("LeftCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> LeftCommand::create()
{
    return std::unique_ptr<LeftCommand>(new LeftCommand());
}

}
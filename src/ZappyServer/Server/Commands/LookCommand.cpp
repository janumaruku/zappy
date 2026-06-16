/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "LookCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool LookCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool LookCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("LookCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> LookCommand::create()
{
    return std::unique_ptr<LookCommand>(new LookCommand());
}

}
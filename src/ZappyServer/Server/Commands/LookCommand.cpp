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

bool LookCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool LookCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Look" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> LookCommand::create()
{
    return std::make_unique<LookCommand>(LookCommand());
}

}
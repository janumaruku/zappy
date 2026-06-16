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

bool LeftCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool LeftCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Left" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> LeftCommand::create()
{
    return std::make_unique<LeftCommand>(LeftCommand());
}

}
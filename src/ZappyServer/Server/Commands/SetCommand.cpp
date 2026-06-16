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

bool SetCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool SetCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Set" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> SetCommand::create()
{
    return std::make_unique<SetCommand>(SetCommand());
}

}
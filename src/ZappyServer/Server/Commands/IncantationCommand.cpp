/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "IncantationCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool IncantationCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool IncantationCommand::execute(const std::vector<std::string> &cmd, AISession &session)
{
    session.send("IncantationCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> IncantationCommand::create()
{
    return std::make_unique<IncantationCommand>(IncantationCommand());
}

}
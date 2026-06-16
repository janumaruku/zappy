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

bool RightCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool RightCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Right" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> RightCommand::create()
{
    return std::make_unique<RightCommand>(RightCommand());
}

}
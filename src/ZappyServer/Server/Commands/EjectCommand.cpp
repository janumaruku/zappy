/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "EjectCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool EjectCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool EjectCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Eject" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> EjectCommand::create()
{
    return std::make_unique<EjectCommand>(EjectCommand());
}

}
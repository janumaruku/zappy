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

bool EjectCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool EjectCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("EjectCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> EjectCommand::create()
{
    return std::unique_ptr<EjectCommand>(new EjectCommand());
}

}
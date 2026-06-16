/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "ForkCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ForkCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool ForkCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("ForkCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> ForkCommand::create()
{
    return std::unique_ptr<ForkCommand>(new ForkCommand());
}

}
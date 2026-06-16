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

bool ForkCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool ForkCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Fork" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> ForkCommand::create()
{
    return std::make_unique<ForkCommand>(ForkCommand());
}

}
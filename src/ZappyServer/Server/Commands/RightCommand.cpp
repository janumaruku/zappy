/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.cpp
*/



#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "RightCommand.hpp"

namespace zappy::server {

bool RightCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    s.send(v[0]);
    return true;
}

bool RightCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> RightCommand::create()
{
    return std::make_unique<RightCommand>(RightCommand());
}

}
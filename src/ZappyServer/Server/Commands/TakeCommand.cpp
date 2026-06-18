/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommand.cpp
*/



#include <format>
#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "TakeCommand.hpp"

namespace zappy::server {

bool TakeCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    s.send(std::format("{} {}", v[0], v[1]));
    return true;
}

bool TakeCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> TakeCommand::create()
{
    return std::make_unique<TakeCommand>(TakeCommand());
}

}
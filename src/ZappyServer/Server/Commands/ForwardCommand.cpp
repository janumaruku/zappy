/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "ForwardCommand.hpp"

namespace zappy::server {

bool ForwardCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    s.send(v[0]);
    return true;
}

bool ForwardCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> ForwardCommand::create()
{
    return std::make_unique<ForwardCommand>(ForwardCommand());
}

}
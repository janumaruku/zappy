/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "LeftCommand.hpp"

namespace zappy::server {

bool LeftCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    s.send(v[0]);
    return true;
}

bool LeftCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> LeftCommand::create()
{
    return std::make_unique<LeftCommand>(LeftCommand());
}

}
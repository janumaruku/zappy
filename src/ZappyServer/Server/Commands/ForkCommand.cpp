/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "ForkCommand.hpp"

namespace zappy::server {

bool ForkCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    s.send(v[0]);
    return true;
}

bool ForkCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> ForkCommand::create()
{
    return std::make_unique<ForkCommand>(ForkCommand());
}

}
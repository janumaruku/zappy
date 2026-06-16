/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "EjectCommand.hpp"

namespace zappy::server {

bool EjectCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    s.send(v[0]);
    return true;
}

bool EjectCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> EjectCommand::create()
{
    return std::make_unique<EjectCommand>(EjectCommand());
}

}
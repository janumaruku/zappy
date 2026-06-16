/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "LookCommand.hpp"

namespace zappy::server {

bool LookCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    return true;
}

bool LookCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> LookCommand::create()
{
    return std::make_unique<LookCommand>(LookCommand());
}

}
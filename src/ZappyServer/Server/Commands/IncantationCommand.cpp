/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "IncantationCommand.hpp"

namespace zappy::server {

bool IncantationCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    
    return true;
}

bool IncantationCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> IncantationCommand::create()
{
    return std::make_unique<IncantationCommand>(IncantationCommand());
}

}
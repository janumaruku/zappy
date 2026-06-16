/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "SetCommand.hpp"

namespace zappy::server {

bool SetCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    
    return true;
}

bool SetCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> SetCommand::create()
{
    return std::make_unique<SetCommand>(SetCommand());
}

}
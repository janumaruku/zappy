/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "ConnectNbrCommand.hpp"

namespace zappy::server {

bool ConnectNbrCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    
    return true;
}

bool ConnectNbrCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> ConnectNbrCommand::create()
{
    return std::make_unique<ConnectNbrCommand>(ConnectNbrCommand());
}

}
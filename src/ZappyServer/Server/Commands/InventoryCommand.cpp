/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "InventoryCommand.hpp"

namespace zappy::server {

bool InventoryCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    return true;
}

bool InventoryCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> InventoryCommand::create()
{
    return std::make_unique<InventoryCommand>(InventoryCommand());
}

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "InventoryCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool InventoryCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool InventoryCommand::execute(const std::vector<std::string> &, AISession &session)
{
    session.send("Inventory" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> InventoryCommand::create()
{
    return std::make_unique<InventoryCommand>(InventoryCommand());
}

}
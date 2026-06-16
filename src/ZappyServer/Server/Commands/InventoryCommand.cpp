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

bool InventoryCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool InventoryCommand::execute(AISession &session, const std::vector<std::string> &)
{
    session.send("InventoryCommand" + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> InventoryCommand::create()
{
    return std::unique_ptr<InventoryCommand>(new InventoryCommand());
}

}
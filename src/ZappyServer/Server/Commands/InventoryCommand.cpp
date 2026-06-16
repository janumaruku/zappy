/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommand.cpp
*/

#include <string>
#include <vector>
#include "Server.hpp"
#include "InventoryCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool InventoryCommand::operator()(AISession &session, const std::vector<std::string> &cmd)
{
    return execute(session, cmd);
}

bool InventoryCommand::execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send("Inventory" + zappy::data::PACKET_END);
    return true;
}

}
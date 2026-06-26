/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** InventoryCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "InventoryCommand.hpp"
#include "Player.hpp"

namespace zappy::server {

bool InventoryCommand::execute(AISession& session, const std::vector<std::string>&)
{
    const Player &player = session.getPlayer();

    const auto &inventory = player.getInventory();

    std::ostringstream out;
    out << "[";
    out << "food " << (inventory.contains(data::Resource::FOOD) ? inventory.at(data::Resource::FOOD) : 0) << ", ";
    out << "linemate " << (inventory.contains(data::Resource::LINEMATE) ? inventory.at(data::Resource::LINEMATE) : 0) << ", ";
    out << "deraumere " << (inventory.contains(data::Resource::DERAUMERE) ? inventory.at(data::Resource::DERAUMERE) : 0) << ", ";
    out << "sibur " << (inventory.contains(data::Resource::SIBUR) ? inventory.at(data::Resource::SIBUR) : 0) << ", ";
    out << "mendiane " << (inventory.contains(data::Resource::MENDIANE) ? inventory.at(data::Resource::MENDIANE) : 0) << ", ";
    out << "phiras " << (inventory.contains(data::Resource::PHIRAS) ? inventory.at(data::Resource::PHIRAS) : 0) << ", ";
    out << "thystame " << (inventory.contains(data::Resource::THYSTAME) ? inventory.at(data::Resource::THYSTAME) : 0);
    out << "]\n";

    session.scheduleResponse(1, out.str());
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

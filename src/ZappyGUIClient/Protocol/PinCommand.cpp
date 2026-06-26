/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** PinCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "GUIPlayer.hpp"
#include "PinCommand.hpp"

namespace zappy::gui {

using Inventory = const std::unordered_map<data::Resource, uint>;

bool PinCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    auto id = cmd.at(0);
    
    if (auto pos = id.find('#'); pos != std::string::npos)
        id.erase(pos, 1);

    auto &player = s.getPlayerById(id);

    player.setPosition({std::stoi(cmd.at(1)), std::stoi(cmd.at(2))});

     Inventory i = {
        {data::Resource::FOOD, std::stoi(cmd.at(3))},
        {data::Resource::LINEMATE,std::stoi(cmd.at(4))},
        {data::Resource::DERAUMERE, std::stoi(cmd.at(5))},
        {data::Resource::SIBUR, std::stoi(cmd.at(6))},
        {data::Resource::MENDIANE, std::stoi(cmd.at(7))},
        {data::Resource::PHIRAS, std::stoi(cmd.at(8))},
        {data::Resource::THYSTAME, std::stoi(cmd.at(9))}
    };
    s.onPlayerInventory(player, i);
    return true;
}

bool PinCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PinCommand::create()
{
    return std::make_unique<PinCommand>(PinCommand());
}
}
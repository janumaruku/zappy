/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** BctCommand.cpp
*/


#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "Tile.hpp"
#include "BctCommand.hpp"

namespace zappy::gui {

bool BctCommand::execute(WorldState&s, const std::vector<std::string>&cmd)
{
    data::Position tilePos(std::stoi(cmd[0]), std::stoi(cmd[1]));

    auto qts = [&cmd]() {
        std::vector<uint> res;
        for (auto it = cmd.begin() + 2; it != cmd.end(); it++)
            res.push_back(static_cast<uint>(std::stoul(*it)));
        return res;
    }();


    if (qts.size() != data::EXISTING_RESSOURCES) {
        std::cerr << "Missing ressources in request" << std::endl;
        return false;
    }

    const std::unordered_map<data::Resource, int> resources = {
        {data::Resource::FOOD, qts[0]},
        {data::Resource::LINEMATE,qts[1]},
        {data::Resource::DERAUMERE, qts[2]},
        {data::Resource::SIBUR, qts[3]},
        {data::Resource::MENDIANE, qts[4]},
        {data::Resource::PHIRAS, qts[5]},
        {data::Resource::THYSTAME, qts[6]}
    };
    s.onTileContent(tilePos, resources);
    return true;
}

bool BctCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> BctCommand::create()
{
    return std::make_unique<BctCommand>(BctCommand());
}
}
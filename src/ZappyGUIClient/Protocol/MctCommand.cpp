/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MctCommand.cpp
*/


#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "MctCommand.hpp"

namespace zappy::gui {

bool MctCommand::execute(WorldState&s, const std::vector<std::string>&cmd)
{

    auto qts = [&cmd]() {
        std::vector<uint> res;
        for (auto it = cmd.begin() + 1; it != cmd.end(); it++)
            res.push_back(static_cast<uint>(std::stoul(*it)));
        return res;
    }();


    if (qts.size() != data::EXISTING_RESSOURCES)
        throw std::invalid_argument("Missing ressources in request");

    const std::unordered_map<data::Resource, uint> resources = {
        {data::Resource::FOOD, qts[0]},
        {data::Resource::LINEMATE,qts[1]},
        {data::Resource::DERAUMERE, qts[2]},
        {data::Resource::SIBUR, qts[3]},
        {data::Resource::MENDIANE, qts[4]},
        {data::Resource::PHIRAS, qts[4]},
        {data::Resource::THYSTAME, qts[5]}
    };

    for (uint y = 0; y != s.getMap().getHeight(); y++)
        for (uint x = 0; x != s.getMap().getHeight(); x++)
            s.onTileContent(data::Position(x, y), resources);
    return true;
}

bool MctCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> MctCommand::create()
{
    return std::make_unique<MctCommand>(MctCommand());
}
}
/*
** EPITECH PROJECT, 2026
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

bool MctCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    constexpr std::size_t fieldsPerTile = 2 + data::EXISTING_RESSOURCES;

    if (cmd.size() % fieldsPerTile != 0)
        return false;

    for (std::size_t i = 0; i < cmd.size(); i += fieldsPerTile) {

        const int x = std::stoi(cmd[i]);
        const int y = std::stoi(cmd[i + 1]);

        auto parseResources = [&](std::size_t offset) {
            std::vector<uint> res;
            res.reserve(data::EXISTING_RESSOURCES);
            for (std::size_t j = 0; j < data::EXISTING_RESSOURCES; ++j)
                res.push_back(static_cast<uint>(std::stoul(cmd[offset + j])));
            return res;
        };

        const auto qts = parseResources(i + 2);

        if (qts.size() != data::EXISTING_RESSOURCES)
            throw std::invalid_argument("Missing ressources in request");

        const std::unordered_map<data::Resource, int> resources = {
            {data::Resource::FOOD, static_cast<int>(qts[0])},
            {data::Resource::LINEMATE, static_cast<int>(qts[1])},
            {data::Resource::DERAUMERE, static_cast<int>(qts[2])},
            {data::Resource::SIBUR, static_cast<int>(qts[3])},
            {data::Resource::MENDIANE, static_cast<int>(qts[4])},
            {data::Resource::PHIRAS, static_cast<int>(qts[5])},
            {data::Resource::THYSTAME, static_cast<int>(qts[6])},
        };

        s.onTileContent(data::Position(x, y), resources);
    }
return true;
}

bool MctCommand::operator()(WorldState &s, const std::vector<std::string> &v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> MctCommand::create()
{
    return std::make_unique<MctCommand>(MctCommand());
}
}

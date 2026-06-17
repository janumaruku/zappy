/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Look command implementation
*/

#include "Look.hpp"

#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

#include "Server.hpp"
#include "Map.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "AISession.hpp"

namespace zappy::server {

static int wrapCoord(int value, int max)
{
    if (max <= 0)
        return value;
    int r = value % max;
    if (r < 0)
        r += max;
    return r;
}

static const std::map<data::Resource, std::string> &resourceNames()
{
    static const std::map<data::Resource, std::string> names = {
        {data::Resource::FOOD, "food"},
        {data::Resource::LINEMATE, "linemate"},
        {data::Resource::DERAUMERE, "deraumere"},
        {data::Resource::SIBUR, "sibur"},
        {data::Resource::MENDIANE, "mendiane"},
        {data::Resource::PHIRAS, "phiras"},
        {data::Resource::THYSTAME, "thystame"},
    };
    return names;
}

static std::vector<data::Position> buildFOVPositions(const data::Position &playerPos,
    data::Orientation orientation, std::uint8_t level, int mapWidth, int mapHeight)
{
    std::vector<data::Position> positions;
    positions.reserve((level + 1) * (level + 1) * 2);

    for (int r = 0; r <= static_cast<int>(level); ++r) {
        for (int i = -r; i <= r; ++i) {
            int x = playerPos.getX();
            int y = playerPos.getY();

            switch (orientation) {
            case data::Orientation::UP:
                x = playerPos.getX() + i;
                y = playerPos.getY() - r;
                break;
            case data::Orientation::RIGHT:
                x = playerPos.getX() + r;
                y = playerPos.getY() + i;
                break;
            case data::Orientation::DOWN:
                x = playerPos.getX() - i;
                y = playerPos.getY() + r;
                break;
            case data::Orientation::LEFT:
                x = playerPos.getX() - r;
                y = playerPos.getY() - i;
                break;
            }

            x = wrapCoord(x, mapWidth);
            y = wrapCoord(y, mapHeight);

            positions.emplace_back(x, y);
        }
    }

    return positions;
}

void Look::execute(AISession &session, Server &server, const std::string &args)
{
    const Player &player = session.getPlayer();
    const Map &map = server.getMap();

    const auto playerPos = player.getPosition();
    const auto level = player.getLevel();
    const auto orientation = player.getOrientation(); 

    const int mapWidth = map.getWidth();
    const int mapHeight = map.getHeight();

    const auto positions = buildFOVPositions(playerPos, orientation, level,
        mapWidth, mapHeight);

    std::ostringstream response;
    response << "[";

    const auto &resNames = resourceNames();

    bool firstTile = true;
    for (const auto &pos : positions) {
        if (!firstTile)
            response << ", ";
        firstTile = false;

        const data::Tile &tile = map.getTile(pos);

        std::vector<std::string> contents;

        if (pos.getX() == playerPos.getX() && pos.getY() == playerPos.getY()) {
            contents.emplace_back("player");
        }

        const auto &resources = tile.getResources();
        for (const auto &kv : resources) {
            const auto &resource = kv.first;
            const auto count = kv.second;
            if (count == 0)
                continue;

            auto it = resNames.find(resource);
            if (it == resNames.end())
                continue;

            for (unsigned int c = 0; c < count; ++c)
                contents.emplace_back(it->second);
        }

        for (size_t i = 0; i < contents.size(); ++i) {
            if (i)
                response << " ";
            response << contents[i];
        }
    }

    response << "]\n";

    session.scheduleResponse(7, response.str());
}

std::unique_ptr<ICommand> Look::create()
{
    return std::make_unique<Look>();
}

} // namespace zappy::server

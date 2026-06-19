/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.cpp
*/



#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "Position.hpp"
#include "Server.hpp"
#include "Tile.hpp"
#include "LookCommand.hpp"

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
    positions.reserve(static_cast<std::uint8_t>((level + 1) * (level + 1) * 2));

    for (int r = 0; r <= static_cast<int>(level); ++r) {
        for (int i = -r; i <= r; ++i) {
            int x = playerPos.getX();
            int y = playerPos.getY();

            switch (orientation) {
            case data::Orientation::UP:
                x += i;
                y -= r;
                break;
            case data::Orientation::RIGHT:
                x += r;
                y += i;
                break;
            case data::Orientation::DOWN:
                x -= i;
                y += r;
                break;
            case data::Orientation::LEFT:
                x -= r;
                y -= i;
                break;
            }

            x = wrapCoord(x, mapWidth);
            y = wrapCoord(y, mapHeight);

            positions.emplace_back(x, y);
        }
    }

    return positions;
}

static void extractResources(
    const data::Tile &tile,
    std::vector<std::string> &contents)
{
    const auto &resNames = resourceNames();
    const auto &resources = tile.getResources();

    for (const auto &kv : resources) {
        const auto &resource = kv.first;
        const auto count = kv.second;
        if (count == 0)
            continue;

        auto it = resNames.find(resource); // 20 lines
        if (it == resNames.end())
            continue;

        for (auto c = 0; c < count; ++c)
            contents.emplace_back(it->second);
    }
}

static void setContentsInResponse(
    std::ostringstream &response,
    const std::vector<std::string> &contents
)
{
    for (size_t i = 0; i < contents.size(); ++i) {
        if (i != 0)
            response << " ";
        response << contents[i];
    }
}

static void checkPlayerPresenceOnTile(
    const AISession &session,
    const data::Position &pos,
    std::vector<std::string> &contents)
{
    if (pos.getX() == session.getPlayer().getPosition().getX()
        && pos.getY() == session.getPlayer().getPosition().getY()) {
        contents.emplace_back("player");
    }
}

static std::string getResponseToString(
    AISession& session,
    const std::vector<data::Position> &positions)
{
    std::ostringstream response;

    response << "[";

    bool firstTile = true;

    for (const auto &pos : positions) {
        if (!firstTile)
            response << ", ";
        firstTile = false;

        const data::Tile &tile = session.getServer().getMap().getTile(pos);

        std::vector<std::string> contents;
        checkPlayerPresenceOnTile(session, pos, contents);
        extractResources(tile, contents);
        setContentsInResponse(response, contents);
    }

    response << "]\n";
    return response.str();
}

bool LookCommand::execute(AISession& session, const std::vector<std::string>& /*v*/)
{
    const std::vector<data::Position> positions = buildFOVPositions(
        session.getPlayer().getPosition(),
        session.getPlayer().getOrientation(),
        session.getPlayer().getLevel(),
        session.getServer().getMap().getWidth(),
        session.getServer().getMap().getHeight());

    std::string response = getResponseToString(session, positions);
    session.scheduleResponse(7, response);
    return true;
}

bool LookCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> LookCommand::create()
{
    return std::make_unique<LookCommand>(LookCommand());
}

}

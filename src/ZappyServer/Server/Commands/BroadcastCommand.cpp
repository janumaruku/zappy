/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include <sstream>
#include <format>
#include <cmath>
#include <cstdlib>

#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "BroadcastCommand.hpp"
#include "Server.hpp"
#include "Position.hpp"
#include "Player.hpp"

namespace zappy::server {

static void computeToroidalDelta(int &dx, int &dy, int mapWidth, int mapHeight)
{
    if (mapWidth > 0) {
        if (std::abs(dx) > mapWidth / 2) {
            if (dx > 0)
                dx -= mapWidth;
            else
                dx += mapWidth;
        }
    }

    if (mapHeight > 0) {
        if (std::abs(dy) > mapHeight / 2) {
            if (dy > 0)
                dy -= mapHeight;
            else
                dy += mapHeight;
        }
    }
}

static int computeGlobalSector(int dx, int dy)
{
    const int absx = std::abs(dx);
    const int absy = std::abs(dy);

    if (absx == 0 && absy == 0)
        return 0;

    if (absy >= 2 * absx) {
        return (dy < 0) ? 1 : 5;
    }

    if (absx >= 2 * absy) {
        return (dx < 0) ? 3 : 7;
    }

    if (dx > 0 && dy < 0)
        return 8;
    if (dx < 0 && dy < 0)
        return 2;
    if (dx < 0 && dy > 0)
        return 4;
    if (dx > 0 && dy > 0)
        return 6;

    if (absy >= absx)
        return (dy < 0) ? 1 : 5;
    return (dx < 0) ? 3 : 7;
}

static int frontGlobalSectorForOrientation(data::Orientation o)
{
    switch (o) {
    case data::Orientation::UP:
        return 1;
    case data::Orientation::RIGHT:
        return 7;
    case data::Orientation::DOWN:
        return 5;
    case data::Orientation::LEFT:
        return 3;
    default:
        return 1;
    }
}

static int computeDirectionK(
    const data::Position &emitterPos,
    const data::Position &receiverPos,
    data::Orientation receiverOrient,
    int mapWidth, int mapHeight)
{
    int dx = emitterPos.getX() - receiverPos.getX();
    int dy = emitterPos.getY() - receiverPos.getY();

    computeToroidalDelta(dx, dy, mapWidth, mapHeight);

    if (dx == 0 && dy == 0)
        return 0;

    const int globalSector = computeGlobalSector(dx, dy);
    const int frontSector = frontGlobalSectorForOrientation(receiverOrient);
    int offset = frontSector - 1;
    int zeroBased = (globalSector - 1 - offset) % 8;

    if (zeroBased < 0)
        zeroBased += 8;
    int k = zeroBased + 1;
    return k;
}

bool BroadcastCommand::execute(
    AISession& session,
    const std::vector<std::string>& parts)
{
    std::string text;

    if (parts.size() <= 1) {
        text = "";
    } else {
        std::ostringstream oss;
        for (std::size_t i = 1; i < parts.size(); ++i) {
            if (i > 1)
                oss << " ";
            oss << parts[i];
        }
        text = oss.str();
    }

    std::string guiMsg = std::format("pbc #{} {}\n",
        session.getPlayer().getId(), text);
    const_cast<Server&>(session.getServer()).notifyGUI(guiMsg);

    std::string aiPayload = std::format("{} {}\n", 0, text);
    const_cast<Server&>(session.getServer()).broadcastToAll(aiPayload);

    session.scheduleResponse(7, "ok\n");
    return true;
}

bool BroadcastCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> BroadcastCommand::create()
{
    return std::make_unique<BroadcastCommand>(BroadcastCommand());
}

} // namespace zappy::server

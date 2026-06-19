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

constexpr uint TIME_LIMIT = 7;
constexpr uint8_t TOTAL_DIRECTION = 8;

enum Sector : std::uint8_t {
    NORTH = 1,
    N_WEST,
    WEST,
    S_WEST,
    SOUTH,
    S_EAST,
    EAST,
    N_EAST,
};

static void computeToroidalDelta(int &dx, int &dy, int mapWidth, int mapHeight)
{
    auto fn = [] (int &delta, int &dimension) {
        if (std::abs(delta) > dimension / 2)
            delta += dimension * (-1 * (delta > 0));
    };

    fn(dx, mapWidth);
    fn(dy, mapHeight);
}

static int computeGlobalSector(int dx, int dy)
{
    const int absx = std::abs(dx);
    const int absy = std::abs(dy);

    if (absx == 0 && absy == 0)
        return 0;

    if (absy >= 2 * absx)
        return (dy < 0) ? Sector::NORTH : Sector::SOUTH;

    if (absx >= 2 * absy)
        return (dx < 0) ? Sector::WEST : Sector::EAST;

    if (dx > 0 && dy < 0)
        return Sector::N_EAST;
    if (dx < 0 && dy < 0)
        return Sector::N_WEST;
    if (dx < 0 && dy > 0)
        return Sector::S_WEST;
    if (dx > 0 && dy > 0)
        return Sector::S_EAST;

    if (absy >= absx)
        return (dy < 0) ? Sector::NORTH : Sector::SOUTH;
    return (dx < 0) ? Sector::WEST : Sector::EAST;
}

static int frontGlobalSectorForOrientation(data::Orientation o)
{
    switch (o) {
    case data::Orientation::UP:
        return Sector::NORTH;
    case data::Orientation::RIGHT:
        return Sector::EAST;
    case data::Orientation::DOWN:
        return Sector::SOUTH;
    case data::Orientation::LEFT:
        return Sector::WEST;
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
    int zeroBased = (globalSector - 1 - offset) % TOTAL_DIRECTION;

    if (zeroBased < 0)
        zeroBased += TOTAL_DIRECTION;
    int k = zeroBased + 1;
    return k;
}

static std::string buildBroadcastText(const std::vector<std::string>& parts)
{
    std::ostringstream oss;

    for (std::size_t i = 1; i < parts.size(); ++i) {
        if (i > 1)
            oss << " ";
        oss << parts[i];
    }
    return oss.str();
}

bool BroadcastCommand::execute(
    AISession& session,
    const std::vector<std::string>& parts)
{
    std::string text;

    if (parts.size() <= 1) {
        text = "";
    } else {
        text = buildBroadcastText(parts);
    }

    std::string guiMsg = std::format("pbc #{} {}\n",
        session.getPlayer().getId(), text);
    session.getServer().notifyGUI(guiMsg);

    const auto emitterPos = session.getPlayer().getPosition();
    const int mapW = session.getServer().getMap().getWidth();
    const int mapH = session.getServer().getMap().getHeight();

    session.getServer().forEachAISession([&](AISession &receiver) {
        int k = computeDirectionK(emitterPos,
            receiver.getPlayer().getPosition(),
            receiver.getPlayer().getOrientation(), mapW, mapH);
        receiver.send(std::format("message {}, {}\n", k, text));
    });

    session.scheduleResponse(TIME_LIMIT, "ok\n");
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

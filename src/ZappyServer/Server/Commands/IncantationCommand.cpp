/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommand.cpp
*/

#include <iostream>
#include <map>
#include <format>

#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "IncantationCommand.hpp"
#include "Server.hpp"
#include "Tile.hpp"
#include "Player.hpp"

namespace zappy::server {

static constexpr uint TIME_LIMIT = 300;

struct ElevationReq {
    ElevationReq(int players, std::array<int, 6> stones):
        players(players), stones(stones)
    {}
    int players;
    std::array<int, 6> stones;
};

static const std::array<ElevationReq, 7> &elevationTable()
{
    static const std::array<ElevationReq, 7> table = {
        ElevationReq{1, {1,0,0,0,0,0}},
        ElevationReq{2, {1,1,1,0,0,0}},
        ElevationReq{2, {2,0,1,0,2,0}},
        ElevationReq{4, {1,1,2,0,1,0}},
        ElevationReq{4, {1,2,1,3,0,0}},
        ElevationReq{6, {1,2,3,0,1,0}},
        ElevationReq{6, {2,2,2,2,2,1}},
    };
    return table;
}

static std::vector<AISession*> gatherParticipants(
    Server &server,
    const data::Position &pos,
    const int level)
{
    std::vector<AISession*> out;
    server.forEachAISession([&](AISession &s) {
        const auto &p = s.getPlayer();
        if (p.getPosition().getX() == pos.getX() &&
            p.getPosition().getY() == pos.getY() &&
            static_cast<int>(p.getLevel()) == level) {
            out.push_back(&s);
        }
    });
    return out;
}

static bool tileHasStones(const data::Tile &tile,
    const std::array<int, 6> &required)
{
    const auto &res = tile.getResources();
    const std::array<data::Resource, 6> order = {
        data::Resource::LINEMATE, data::Resource::DERAUMERE,
        data::Resource::SIBUR, data::Resource::MENDIANE,
        data::Resource::PHIRAS, data::Resource::THYSTAME
    };
    for (size_t i = 0; i < order.size(); i += 1) {
        auto it = res.find(order[i]);
        const uint have = (it == res.end()) ? 0 : it->second;
        if (have < static_cast<uint>(required[i]))
            return false;
    }
    return true;
}

static void consumeStones(Server &server,
    const data::Position &pos, const std::array<int,6> &required)
{
    const std::array<data::Resource, 6> order = {
        data::Resource::LINEMATE, data::Resource::DERAUMERE,
        data::Resource::SIBUR, data::Resource::MENDIANE,
        data::Resource::PHIRAS, data::Resource::THYSTAME
    };
    for (size_t i = 0; i < order.size(); i += 1) {
        for (int c = 0; c < required[i]; c += 1)
            (void)server.getMap().takeResource(order[i], pos);
    }
}

bool IncantationCommand::execute(AISession &session,
    const std::vector<std::string> &)
{
    Server &server = session.getServer();
    const auto pos = session.getPlayer().getPosition();
    const int level = static_cast<int>(session.getPlayer().getLevel());

    if (level < 1 || level > 7) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    const auto &req = elevationTable()[level - 1];

    auto participants = gatherParticipants(server, pos, level);
    if (static_cast<int>(participants.size()) != req.players) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    const data::Tile &tile = server.getMap().getTile(pos);
    if (!tileHasStones(tile, req.stones)) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    for (auto *p : participants)
        p->freeze();

    std::string pic = std::format("pic {} {} {}",
        pos.getX(), pos.getY(), level);
    for (auto *p : participants)
        pic += std::format(" #{}", p->getPlayer().getId());
    pic += "\n";
    server.broadcastToAll(pic);
    server.notifyGUI(pic);

    session.scheduleTask(TIME_LIMIT, [=, &server]() mutable {
        auto endParticipants = gatherParticipants(server, pos, level);
        const data::Tile &endTile = server.getMap().getTile(pos);
        bool stonesOk = tileHasStones(endTile, req.stones);
        bool playersOk = static_cast<int>(endParticipants.size()) == req.players;

        if (!playersOk || !stonesOk) {
            for (auto *p : endParticipants) {
                p->unfreeze();
                p->send("ko\n");
            }
            std::string pieFail = std::format("pie {} {} 0\n",
                pos.getX(), pos.getY());
            server.notifyGUI(pieFail);
            return;
        }

        consumeStones(server, pos, req.stones);
        for (auto *p : endParticipants) {
            Player &pl = p->getPlayer();
            pl.takeResource(data::Resource::FOOD);
        }

        for (auto *p : endParticipants) {
            const int newLevel = static_cast<int>(p->getPlayer().getLevel()) + 1;
            p->send(std::format("Current level: {}\n", newLevel));
            p->unfreeze();
        }

        auto winner = server.checkWinCondition();
        if (winner) {
            server.broadcastToAll(std::format("seg {}\n", *winner));
            std::exit(0);
        }

        std::string pie = std::format("pie {} {} 1\n", pos.getX(), pos.getY());
        server.notifyGUI(pie);
    });

    return true;
}

bool IncantationCommand::operator()(AISession &s,
    const std::vector<std::string> &v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> IncantationCommand::create()
{
    return std::make_unique<IncantationCommand>(IncantationCommand());
}

} // namespace zappy::server

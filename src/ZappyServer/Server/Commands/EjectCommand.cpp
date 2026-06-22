/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.cpp
*/

#include "EjectCommand.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Server.hpp"
#include <algorithm>
#include <format>
#include <memory>

namespace zappy::server {

bool EjectCommand::execute(AISession& s, const std::vector<std::string>& /*v*/)
{
    auto& player = s.getPlayer();
    auto pos = player.getPosition();
    auto orientation = player.getOrientation();
    bool actionTaken = false;
    std::vector<std::unique_ptr<AISession>> playersToPush;

    s.getServer().forEachAISession([&](AISession& other) {
        if (&other != &s && other.getPlayer().getPosition().getX() == pos.getX() &&
            other.getPlayer().getPosition().getY() == pos.getY()) {
            playersToPush.emplace_back(&other);
        }
    });

    for (auto& otherSession : playersToPush) {
        actionTaken = true;
        auto& otherPlayer = otherSession->getPlayer();
        (void)orientation;

        std::string fmt = std::format("pex {}\n", otherPlayer.getId());
        s.getServer().notifyGUI(fmt);
        otherSession->send("eject: 1\n");
    }

    s.scheduleResponse(7, actionTaken ? "ok\n" : "ko\n");
    return true;
}

bool EjectCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> EjectCommand::create()
{
    return std::make_unique<EjectCommand>();
}

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.cpp
*/

#include "EjectCommand.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Position.hpp"
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
    std::vector<AISession *> playersToPush;

    s.getServer().forEachAISession([&](AISession& other) {
        const auto &otherPos = other.getPlayer().getPosition();
        if (&other != &s && otherPos.getX() == pos.getX() &&
            otherPos.getY() == pos.getY()) {
            playersToPush.push_back(&other);
        }
    });

    auto eggs = s.getServer().getMap().getEggsOnTile(pos);

    for (auto& egg : eggs) {
        s.getServer().getMap().removeEgg(egg);
        s.getServer().notifyGUI(std::format("edi #{}", egg));
    }

    for (auto& otherSession : playersToPush) {
        actionTaken = true;
        auto& otherPlayer = otherSession->getPlayer();
        (void)orientation;

        std::string fmt = std::format("pex #{}\n", otherPlayer.getId());
        s.getServer().notifyGUI(fmt);
        otherSession->send(
            std::format("eject: {}\n", static_cast<uint8_t>(orientation)));
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

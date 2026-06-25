/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** ForwardCommand.cpp
*/



#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "ForwardCommand.hpp"

namespace zappy::server {

bool ForwardCommand::execute(AISession& s, const std::vector<std::string>& /*v*/)
{
    auto &player = s.getPlayer();
    auto &server = s.getServer();

    player.forward();
    server.notifyGUI(std::format("ppo #{} {} {} {}\n",
        player.getId(), player.getPosition().getX(),
        player.getPosition().getY(), static_cast<int>(player.getOrientation()) + 1));
    s.scheduleResponse(7, "ok\n");
    return true;
}

bool ForwardCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> ForwardCommand::create()
{
    return std::make_unique<ForwardCommand>(ForwardCommand());
}

}
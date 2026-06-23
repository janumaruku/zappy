/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.cpp
*/



#include <format>
#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "LeftCommand.hpp"

namespace zappy::server {

bool LeftCommand::execute(AISession& s, const std::vector<std::string>& /*v*/)
{
    auto &player = s.getPlayer();
    auto &server = s.getServer();

    player.left();
    server.notifyGUI(std::format("ppo #{} {} {} {}\n",
        player.getId(), player.getPosition().getX(),
        player.getPosition().getY(), static_cast<int>(player.getOrientation()) + 1));
    s.scheduleResponse(7, "ok\n");
    return true;
}

bool LeftCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> LeftCommand::create()
{
    return std::make_unique<LeftCommand>();
}

}
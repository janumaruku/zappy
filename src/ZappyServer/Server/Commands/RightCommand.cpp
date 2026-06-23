/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.cpp
*/



#include <format>
#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "RightCommand.hpp"

namespace zappy::server {

bool RightCommand::execute(AISession& s, const std::vector<std::string>& /*v*/)
{
    auto &player = s.getPlayer();
    auto &server = s.getServer();

    player.right();
    server.notifyGUI(std::format("ppo #{} {} {} {}\n",
        player.getId(), player.getPosition().getX(),
        player.getPosition().getY(), static_cast<int>(player.getOrientation()) + 1));
    s.scheduleResponse(7, "ok\n");
    return true;
}

bool RightCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> RightCommand::create()
{
    return std::make_unique<RightCommand>();
}

}
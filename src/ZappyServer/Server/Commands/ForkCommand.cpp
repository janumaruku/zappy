/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.cpp
*/

#include <memory>
#include <string>
#include <vector>
#include <format>

#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "ForkCommand.hpp"
#include "Server.hpp"
#include "Egg.hpp"
#include "Player.hpp"

namespace zappy::server {

static constexpr uint TIME_LIMIT = 42;

bool ForkCommand::execute(AISession &session,
    const std::vector<std::string> &)
{
    Server &server = session.getServer();
    const Player &player = session.getPlayer();
    const auto pos = player.getPosition();

    uint nextId = 1;
    const auto &eggs = server.getMap().getEggs();
    for (const auto &kv : eggs)
        nextId = std::max(nextId, kv.first + 1);

    std::string eggId = std::to_string(nextId);
    data::Egg egg(eggId, player.getId(), player.getTeam(), pos, 0);
    server.getMap().addEgg(egg);

    server.notifyGUI(std::format("pfk #{}\n", player.getId()));
    server.notifyGUI(std::format("enw #{} #{} {} {}\n",
        eggId, player.getId(), pos.getX(), pos.getY()));

    session.scheduleResponse(TIME_LIMIT, "ok\n");
    return true;
}

bool ForkCommand::operator()(AISession &s,
    const std::vector<std::string> &v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> ForkCommand::create()
{
    return std::make_unique<ForkCommand>(ForkCommand());
}

} // namespace zappy::server

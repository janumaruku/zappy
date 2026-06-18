/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.cpp
*/

#include <format>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "SetCommand.hpp"
#include "Server.hpp"
#include "Player.hpp"

namespace zappy::server {

constexpr uint TIME_LIMIT = 7;

static const std::unordered_map<std::string, data::Resource> &resName()
{
    static const std::unordered_map<std::string, data::Resource> m = {
        {"food", data::Resource::FOOD},
        {"linemate", data::Resource::LINEMATE},
        {"deraumere", data::Resource::DERAUMERE},
        {"sibur", data::Resource::SIBUR},
        {"mendiane", data::Resource::MENDIANE},
        {"phiras", data::Resource::PHIRAS},
        {"thystame", data::Resource::THYSTAME},
    };
    return m;
}

bool SetCommand::execute(AISession &session,
    const std::vector<std::string> &parts)
{
    if (parts.size() < 2) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    const auto &map = resName();
    const auto it = map.find(parts[1]);
    if (it == map.end()) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    const auto resource = it->second;
    Server &server = const_cast<Server &>(session.getServer());
    Player &player = const_cast<Player &>(session.getPlayer());

    if (!player.removeResource(resource)) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    const auto pos = session.getPlayer().getPosition();
    server.getMap().dropResource(resource, pos);

    std::string guiMsg = std::format("pdr #{} {}\n",
        session.getPlayer().getId(), static_cast<int>(resource));
    server.notifyGUI(guiMsg);

    session.scheduleResponse(TIME_LIMIT, "ok\n");
    return true;
}

bool SetCommand::operator()(AISession &s,
    const std::vector<std::string> &v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> SetCommand::create()
{
    return std::make_unique<SetCommand>(SetCommand());
}

} // namespace zappy::server
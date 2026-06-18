/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommand.cpp
*/

#include <exception>
#include <format>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>

#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "TakeCommand.hpp"
#include "Server.hpp"
#include "Player.hpp"

namespace zappy::server {

static constexpr uint8_t TIME_LIMIT = 7;

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

bool TakeCommand::execute(AISession &session,
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
    auto &server = const_cast<Server &>(session.getServer());

    const auto pos = session.getPlayer().getPosition();
    bool taken = false;
    try {
        taken = server.getMap().takeResource(resource, pos);
    } catch (const std::out_of_range &e) {
        std::cerr << "TakeCommand: invalid position: " << e.what() << std::endl;
        taken = false;
    } catch (const std::exception &e) {
        std::cerr << "TakeCommand: unexpected exception: " << e.what() << std::endl; 
        taken = false;
    }

    if (!taken) {
        session.scheduleResponse(TIME_LIMIT, "ko\n");
        return true;
    }

    auto &player = const_cast<Player &>(session.getPlayer());
    player.takeResource(resource);

    std::string guiMsg = std::format("pbc #{} {}\n",
        session.getPlayer().getId(), static_cast<int>(resource));
    server.notifyGUI(guiMsg);

    session.scheduleResponse(TIME_LIMIT, "ok\n");
    return true;
}

bool TakeCommand::operator()(AISession &s, const std::vector<std::string> &v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> TakeCommand::create()
{
    return std::make_unique<TakeCommand>(TakeCommand());
}

} // namespace zappy::server
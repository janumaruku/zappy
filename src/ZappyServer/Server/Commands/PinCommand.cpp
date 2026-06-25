/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** PinCommand.cpp
*/

#include "PinCommand.hpp"

#include <array>
#include <memory>
#include <sstream>
#include <string>

#include "GUISession.hpp"
#include "Player.hpp"
#include "Server.hpp"
#include "Tile.hpp"

namespace zappy::server {

static std::string protocolPlayerId(const std::string &arg)
{
    if (!arg.empty() && arg.front() == '#')
        return arg.substr(1);
    return arg;
}

static int inventoryCount(const Player &player, const data::Resource &resource)
{
    const auto &inventory = player.getInventory();

    if (!inventory.contains(resource))
        return 0;
    return inventory.at(resource);
}

bool PinCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    const auto &map = session.getServer().getMap();
    const std::string playerId = args.empty() ? "" : protocolPlayerId(args[0]);

    if (playerId.empty() || !map.hasPlayer(playerId)) {
        session.send("suc\n");
        return false;
    }

    const Player &player = map.getPlayer(playerId);
    const auto position = player.getPosition();
    constexpr std::array resources = {
        data::Resource::FOOD,
        data::Resource::LINEMATE,
        data::Resource::DERAUMERE,
        data::Resource::SIBUR,
        data::Resource::MENDIANE,
        data::Resource::PHIRAS,
        data::Resource::THYSTAME,
    };
    std::ostringstream out;

    out << "pin #" << player.getId() << ' '
        << position.getX() << ' ' << position.getY();
    for (const auto &resource : resources)
        out << ' ' << inventoryCount(player, resource);
    out << "\n";
    session.send(out.str());
    return true;
}

bool PinCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> PinCommand::create()
{
    return std::make_unique<PinCommand>();
}

}

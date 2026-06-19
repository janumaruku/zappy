/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PnwCommand.cpp
*/

#include "PnwCommand.hpp"

#include <memory>
#include <sstream>
#include <string>

#include "GUISession.hpp"
#include "Player.hpp"
#include "Server.hpp"

namespace zappy::server {

static int protocolOrientation(const Player &player)
{
    return static_cast<int>(player.getOrientation()) + 1;
}

static void sendPlayerNew(GUISession &session, const Player &player)
{
    std::ostringstream out;
    const auto position = player.getPosition();

    out << "pnw #" << player.getId() << ' '
        << position.getX() << ' ' << position.getY() << ' '
        << protocolOrientation(player) << ' '
        << static_cast<int>(player.getLevel()) << ' '
        << player.getTeam() << "\n";
    session.send(out.str());
}

bool PnwCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    const auto &map = session.getServer().getMap();

    if (args.empty()) {
        for (const auto &[_, player] : map.getPlayers())
            sendPlayerNew(session, player);
        return true;
    }
    if (!map.hasPlayer(args[0]))
        return false;
    sendPlayerNew(session, map.getPlayer(args[0]));
    return true;
}

bool PnwCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> PnwCommand::create()
{
    return std::make_unique<PnwCommand>();
}

}

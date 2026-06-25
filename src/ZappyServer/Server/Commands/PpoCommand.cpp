/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** PpoCommand.cpp
*/

#include "PpoCommand.hpp"

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

bool PpoCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    const auto &map = session.getServer().getMap();

    if (args.empty() || !map.hasPlayer(args[0]))
        return false;

    const Player &player = map.getPlayer(args[0]);
    const auto position = player.getPosition();
    std::ostringstream out;

    out << "ppo #" << player.getId() << ' '
        << position.getX() << ' ' << position.getY() << ' '
        << protocolOrientation(player) << "\n";
    session.send(out.str());
    return true;
}

bool PpoCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> PpoCommand::create()
{
    return std::make_unique<PpoCommand>();
}

}

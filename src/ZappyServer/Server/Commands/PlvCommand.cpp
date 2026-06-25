/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** PlvCommand.cpp
*/

#include "PlvCommand.hpp"

#include <memory>
#include <sstream>
#include <string>

#include "GUISession.hpp"
#include "Player.hpp"
#include "Server.hpp"

namespace zappy::server {

static std::string protocolPlayerId(const std::string &arg)
{
    if (!arg.empty() && arg.front() == '#')
        return arg.substr(1);
    return arg;
}

bool PlvCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    const auto &map = session.getServer().getMap();
    const std::string playerId = args.empty() ? "" : protocolPlayerId(args[0]);

    if (playerId.empty() || !map.hasPlayer(playerId)) {
        session.send("suc\n");
        return false;
    }

    const Player &player = map.getPlayer(playerId);
    std::ostringstream out;

    out << "plv #" << player.getId() << ' '
        << static_cast<int>(player.getLevel()) << "\n";
    session.send(out.str());
    return true;
}

bool PlvCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> PlvCommand::create()
{
    return std::make_unique<PlvCommand>();
}

}

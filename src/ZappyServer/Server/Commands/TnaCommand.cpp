/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TnaCommand.cpp
*/

#include "TnaCommand.hpp"

#include <memory>
#include <string>

#include "GUISession.hpp"
#include "Server.hpp"

namespace zappy::server {

bool TnaCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    if (args.empty()) {
        for (const auto &team : session.getServer().getTeams())
            session.send("tna " + team + "\n");
        return true;
    }
    session.send("tna " + args[0] + "\n");
    return true;
}

bool TnaCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> TnaCommand::create()
{
    return std::make_unique<TnaCommand>();
}

}

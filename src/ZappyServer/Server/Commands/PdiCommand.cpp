/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PdiCommand.cpp
*/

#include "PdiCommand.hpp"

#include <memory>
#include <string>
#include <vector>

#include "GUISession.hpp"

namespace zappy::server {

bool PdiCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    if (args.empty())
        return false;

    session.send("pdi #" + args[0] + "\n");
    return true;
}

bool PdiCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> PdiCommand::create()
{
    return std::make_unique<PdiCommand>();
}

}

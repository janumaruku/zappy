/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PdiCommand.cpp
*/


#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "GUIPlayer.hpp"
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "PdiCommand.hpp"

namespace zappy::gui {

bool PdiCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    auto id = cmd[0];

    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());

    s.onPlayerDeath(id);
    return true;
}

bool PdiCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PdiCommand::create()
{
    return std::make_unique<PdiCommand>(PdiCommand());
}
}
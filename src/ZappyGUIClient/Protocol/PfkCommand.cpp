/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PfkCommand.cpp
*/


#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "PfkCommand.hpp"

namespace zappy::gui {

bool PfkCommand::execute(WorldState& s, const std::vector<std::string>&cmd)
{
    auto id = cmd[0];

    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());

    auto &player = s.getPlayerById(id);
    s.onEggLaid(static_cast<int>(s.getEggs().size() + 1), id, player.getPosition());
    return true;
}

bool PfkCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PfkCommand::create()
{
    return std::make_unique<PfkCommand>(PfkCommand());
}
}
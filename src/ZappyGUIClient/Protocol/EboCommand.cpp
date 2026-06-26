/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** EboCommand.cpp
*/


#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "EboCommand.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

bool EboCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    auto id = cmd[0];

    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());

    s.onEggHatched(std::stoi(id));
    return true;
}

bool EboCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> EboCommand::create()
{
    return std::make_unique<EboCommand>(EboCommand());
}
}

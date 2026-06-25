/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SgtCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "GUIPlayer.hpp"
#include "SgtCommand.hpp"

namespace zappy::gui {

using Inventory = const std::unordered_map<data::Resource, uint>;

bool SgtCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    s.onTimeUnit(std::stoi(cmd[0]));
    return true;
}

bool SgtCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> SgtCommand::create()
{
    return std::make_unique<SgtCommand>(SgtCommand());
}
}
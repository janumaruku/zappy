/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SstCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "GUIPlayer.hpp"
#include "SstCommand.hpp"

namespace zappy::gui {

using Inventory = const std::unordered_map<data::Resource, uint>;

bool SstCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    s.onTimeUnit(std::stoi(cmd[0]));
    return true;
}

bool SstCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> SstCommand::create()
{
    return std::make_unique<SstCommand>(SstCommand());
}
}
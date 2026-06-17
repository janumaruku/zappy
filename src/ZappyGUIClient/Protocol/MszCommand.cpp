/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MszCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "MszCommand.hpp"

namespace zappy::gui {

bool MszCommand::execute(WorldState& s, const std::vector<std::string>&cmd)
{
    s.getMap().updateWidth(std::stoi(cmd[0]));
    s.getMap().updateHeight(std::stoi(cmd[1]));
    return true;
}

bool MszCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> MszCommand::create()
{
    return std::make_unique<MszCommand>(MszCommand());
}
}
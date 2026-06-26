/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SmgCommand.cpp
*/


#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "GUIPlayer.hpp"
#include "SmgCommand.hpp"

namespace zappy::gui {

bool SmgCommand::execute(WorldState &, const std::vector<std::string> &cmd)
{
    const auto &message = cmd.at(0);
    std::clog << message << std::endl;
    return true;
}

bool SmgCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> SmgCommand::create()
{
    return std::make_unique<SmgCommand>(SmgCommand());
}
}
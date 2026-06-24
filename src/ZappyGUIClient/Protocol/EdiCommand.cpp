/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EdiCommand.cpp
*/


#include <cstdint>
#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "GUIPlayer.hpp"
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "EdiCommand.hpp"

namespace zappy::gui {

bool EdiCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    s.onEggDeath(cmd[0]);
    return true;
}

bool EdiCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> EdiCommand::create()
{
    return std::make_unique<EdiCommand>(EdiCommand());
}
}
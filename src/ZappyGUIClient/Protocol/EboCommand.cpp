/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EboCommand.cpp
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
#include "EboCommand.hpp"

namespace zappy::gui {

bool EboCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    s.onEggHatched(cmd[0]);
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
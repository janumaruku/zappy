/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** PbcCommand.cpp
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
#include "PbcCommand.hpp"

namespace zappy::gui {

bool PbcCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    auto id = cmd[0];

    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());
    const auto &message = cmd[1];
    s.onPlayerBroadcast(id, message);
    return true;
}

bool PbcCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PbcCommand::create()
{
    return std::make_unique<PbcCommand>(PbcCommand());
}
}
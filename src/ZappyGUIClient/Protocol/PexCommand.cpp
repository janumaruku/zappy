/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PexCommand.cpp
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
#include "PexCommand.hpp"

namespace zappy::gui {

bool PexCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    auto id = cmd[0];

    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());

    s.onPlayerEject(id);
    return true;
}

bool PexCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PexCommand::create()
{
    return std::make_unique<PexCommand>(PexCommand());
}
}
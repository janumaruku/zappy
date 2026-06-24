/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TnaCommand.cpp
*/

#include <algorithm>
#include <charconv>
#include <cstddef>
#include <exception>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "GUIPlayer.hpp"
#include "TnaCommand.hpp"

namespace zappy::gui {

bool TnaCommand::execute(WorldState& s, const std::vector<std::string>&cmd)
{
    for (const auto &teamName : cmd)
        s.onTeamName(teamName);
    return true;
}

bool TnaCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> TnaCommand::create()
{
    return std::make_unique<TnaCommand>(TnaCommand());
}
}
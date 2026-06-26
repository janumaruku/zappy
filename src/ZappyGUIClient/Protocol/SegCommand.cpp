/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SegCommand.cpp
*/

#include <memory>
#include <raylib.h>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "Team.hpp"
#include "SegCommand.hpp"

namespace zappy::gui {

bool SegCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    auto team = s.getTeams().at(cmd.at(0));
    s.onGameEnd(team);
    return true;
}

bool SegCommand::operator()(WorldState &s, const std::vector<std::string> &v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> SegCommand::create()
{
    return std::make_unique<SegCommand>(SegCommand());
}
}

/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PicCommand.cpp
*/


#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Egg.hpp"
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "PicCommand.hpp"

namespace zappy::gui {


bool PicCommand::execute(WorldState& s, const std::vector<std::string>&cmd)
{
    data::Position pos(std::stoi(cmd.at(0)), std::stoi(cmd.at(1)));
    uint level = std::stoi(cmd.at(2));

    auto initiatorId = cmd.at(3);

    if (!initiatorId.empty() && initiatorId.front() == '#')
        initiatorId.erase(initiatorId.begin());

    std::vector<data::PlayerId> participants(cmd.begin() + 4, cmd.end());

    s.onIncantationStart(pos, level, initiatorId, participants);
    return true;
}

bool PicCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PicCommand::create()
{
    return std::make_unique<PicCommand>(PicCommand());
}
}
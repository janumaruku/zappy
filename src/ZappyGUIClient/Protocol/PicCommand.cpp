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
    data::Position pos;
    uint level;

    try {
        pos = data::Position(std::stoi(cmd[0]), std::stoi(cmd[1]));
        level = std::stoi(cmd[2]);
    } catch (const std::exception &e) {
        std::cerr << "PicCommand::" << __func__ << "Error Parsing position";
        return false;
    }
    std::vector<data::PlayerId> playerIds;
    for (auto it = cmd.begin() + 3; it != cmd.end(); it++)
        playerIds.push_back(*it);
    s.onIncantationStart(pos, level, playerIds);
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
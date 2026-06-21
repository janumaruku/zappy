/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EnwCommand.cpp
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
#include "EnwCommand.hpp"

namespace zappy::gui {

bool EnwCommand::execute(WorldState &s, const std::vector<std::string> &cmd)
{
    auto eggId = cmd[0];
    auto playerId = cmd[1];
    data::Position pos;

    try {
        pos = data::Position(std::stoi(cmd[2]), std::stoi(cmd[3]));
    } catch (const std::exception &e) {
        std::cerr << "EnwCommand::" << __func__ << "Error Parsing position";
        return false;
    }
    s.onEggLaid(eggId, playerId, pos);
    return true;
}

bool EnwCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> EnwCommand::create()
{
    return std::make_unique<EnwCommand>(EnwCommand());
}
}
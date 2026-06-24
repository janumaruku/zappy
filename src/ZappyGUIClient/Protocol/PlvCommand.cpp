/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PlvCommand.cpp
*/


#include <algorithm>
#include <charconv>
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
#include "PlvCommand.hpp"

namespace zappy::gui {

bool PlvCommand::execute(WorldState& s, const std::vector<std::string>&cmd)
{
    const auto &str = cmd.at(0);
    auto &player = s.getPlayerById(str);

    player.setLevel(std::stoi(str));
    s.onPlayerLevel(player);
    return true;
}

bool PlvCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PlvCommand::create()
{
    return std::make_unique<PlvCommand>(PlvCommand());
}
}
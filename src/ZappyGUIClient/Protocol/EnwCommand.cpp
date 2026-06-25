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

    auto eggId = cmd.at(0);
    auto playerId = cmd.at(1);

    auto stripHastag = [] (std::string &str) {
        if (!str.empty() && str.front() == '#')
        str.erase(str.begin());
    };
    stripHastag(eggId);
    stripHastag(playerId);
    
    s.onEggLaid(std::stoi(eggId), playerId, s.getPlayerById(playerId).getPosition());
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
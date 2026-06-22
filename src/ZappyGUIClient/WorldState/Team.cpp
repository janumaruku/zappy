/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Team.cpp
*/

#include "Team.hpp"

#include <iostream>

namespace zappy::gui {

Team::Team(const std::string &name, const Color &color): _name(name)
, _color(color)
{

}

std::string Team::getName() const
{
    return _name;
}

Color Team::getColor() const
{
    return _color;
}

void Team::addPlayer(const PlayerId &id)
{
    _players.push_back(id);
}

void Team::removePlayer(const PlayerId &id)
{
    const auto it = std::ranges::find(_players, id);

    if (it == _players.end()) {
        std::clog << "Couldn't find player: " << id << std::endl;
        return;
    }
    _players.erase(it);
    std::clog << "Removed player: " << id << std::endl;
}
}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Team.cpp
*/

#include "Team.hpp"

#include <iostream>

namespace zappy::gui {

Team::Team(std::string name/*, Color color*/): _name(name) /*, _color(color)*/
{

}

std::string Team::getName()
{
    return _name;
}

/*Team::Color Team::getColor()
{
    return _color;
}*/

void Team::addPlayer(PlayerId id)
{
    _players.push_back(id);
}

void Team::removePlayer(PlayerId id)
{
    auto lastSize = _players.size();
    _players.remove(id);

    if (_players.size() >= lastSize) {
        std::clog << "Couldn't find player: " << id << std::endl;
    } else {
        std::clog << "Removed player: " << id << std::endl;
    }
}
}

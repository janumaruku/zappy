/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIEgg.cpp
*/

#include "Egg.hpp"

namespace zappy::data {
Egg::Egg(const std::string &id, const PlayerId &playerId,
    const std::string &team, const Position &position,
    uint level):
    _id(id), _playerId(playerId), _team(team), _position(position),
    _level(level)
{
}

std::string Egg::getId() const
{
    return _id;
}

PlayerId Egg::getPlayerId() const
{
    return _playerId;
}

Position Egg::getPosition() const
{
    return _position;
}

std::string Egg::getTeam() const
{
    return _team;
}

uint Egg::getLevel() const
{
    return _level;
}

}

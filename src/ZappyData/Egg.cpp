/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIEgg.cpp
*/

#include "Egg.hpp"

#include <utility>

namespace zappy::data {
Egg::Egg(std::string id, PlayerId playerId,
    std::string team, Position position,
    uint level):
    _id(std::move(id)),
    _playerId(std::move(playerId)),
    _team(std::move(team)),
    _position(position),
    _level(level)
{}

std::string Egg::getId() const
{
    return _id;
}

const PlayerId &Egg::getPlayerId() const
{
    return _playerId;
}

Position Egg::getPosition() const
{
    return _position;
}

TeamId &Egg::getTeam()
{
    return _team;
}

const TeamId &Egg::getTeam() const
{
    return _team;
}

uint Egg::getLevel() const
{
    return _level;
}

}

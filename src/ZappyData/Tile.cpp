/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Tile.cpp
*/

#include "include/Tile.hpp"

#include <algorithm>

namespace zappy::data {
Tile::Tile(const Position position): _position(position)
{
    for (auto i = 0; i < 7; ++i)
        _resources[static_cast<Resource>(i)] = 0;

}

Position Tile::getPosition() const
{
    return _position;
}

const std::unordered_map<Resource, int> &Tile::getResources() const
{
    return _resources;
}

const std::vector<PlayerId> &Tile::getPlayers() const
{
    return _players;
}

void Tile::setResources(const std::unordered_map<Resource, int> &resources)
{
    _resources = resources;
}

void Tile::addResources(const std::unordered_map<Resource, int> &resources)
{
    for (const auto &[resource, count]: resources)
        _resources.at(resource) += count;
}

bool Tile::hasResource(const Resource &resource) const
{
    return _resources.at(resource) != 0;
}

void Tile::takeResource(const Resource &resource)
{
    _resources.at(resource)--;
}

void Tile::dropResource(const Resource &resource)
{
    _resources.at(resource)++;
}

void Tile::addPlayer(const PlayerId &id)
{
    _players.push_back(id);
}

void Tile::removePlayer(const PlayerId &id)
{
    std::erase(_players, id);
}
}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Tile.cpp
*/

#include "include/Tile.hpp"

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
}

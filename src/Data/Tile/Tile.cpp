/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

#include <iostream>
#include <ostream>

namespace zappy::data {
Tile::Tile(const Position position, const std::map<Resource, uint> &resources,
    const uint egg): _position(position), _resources(resources), _egg(egg)
{

}

Tile::Tile(const Position position, const uint egg): _position(position),
    _egg(egg)
{

}

Position Tile::getPosition() const
{
    return _position;
}

std::map<Resource, uint> &Tile::getResources()
{
    return _resources;
}

std::string Tile::getResourceName(const Resource resource)
{
    switch (resource) {
    case Resource::FOOD:
        return "Food";
    case Resource::LINEMATE:
        return "Linemate";
    case Resource::DERAUMERE:
        return "Deraumere";
    case Resource::SIBUR:
        return "Sibur";
    case Resource::MENDIANE:
        return "Mendiane";
    case Resource::PHIRAS:
        return "Phiras";
    case Resource::THYSTAME:
        return "Thystame";
    default:
        return "Unkown resource";
    }
}

std::string Tile::getResourcesAsString() const
{
    std::string res;

    for (const auto &it: _resources) {
        res += getResourceName(it.first) + ": " + std::to_string(it.second) +
            "\n";
    }
    return res;
}

uint Tile::getNumberOfEggs() const
{
    return _egg;
}
}

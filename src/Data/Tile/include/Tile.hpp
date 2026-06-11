/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP
#define TILE_HPP
#include <list>
#include <map>
#include <string>
#include <sys/types.h>

#include "Position.hpp"

namespace zappy::data {
using PlayerId = std::string;

enum class Resource {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
};

class Tile {
public:
    Tile(Position position, const std::map<Resource, uint> &resources,
        uint egg);

    Position getPosition() const;

    std::map<Resource, uint> getResources();

    std::string getResourcesAsString() const;

    uint getNumberOfEggs() const;

private:
    Position _position;
    std::map<Resource, uint> _resources;
    std::list<PlayerId> _players;
    uint _egg = 0;

    static std::string getResourceName(Resource resource);
};
}

#endif

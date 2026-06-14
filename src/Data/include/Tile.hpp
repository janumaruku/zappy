/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP
#define TILE_HPP
#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <sys/types.h>

#include "Position.hpp"

namespace zappy::data {
using PlayerId = std::string;

enum class Resource : std::uint8_t {
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
    Tile(Position position, const std::map<Resource, uint> &resources);

    Tile(Position position);

    [[nodiscard]] Position getPosition() const;

    std::map<Resource, uint> &getResources();

    [[nodiscard]] std::string getResourcesAsString() const;

private:
    Position _position;
    std::map<Resource, uint> _resources;

    static std::string getResourceName(Resource resource);
};
}

#endif

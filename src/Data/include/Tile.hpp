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
#include <unordered_map>
#include <sys/types.h>

#include "Position.hpp"

namespace zappy::data {
using PlayerId = std::string;

enum class Resource : std::uint8_t {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
};

class Tile {
public:
    explicit Tile(Position position);

    [[nodiscard]] Position getPosition() const;

    [[nodiscard]] const std::unordered_map<Resource, uint> &
    getResources() const;

    void setResources(const std::unordered_map<Resource, uint> &resources);

private:
    Position _position;
    std::unordered_map<Resource, uint> _resources;
};
}

#endif

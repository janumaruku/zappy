/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP
#define TILE_HPP
#include <cstddef>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <sys/types.h>

#include "Position.hpp"

namespace zappy::data {
using PlayerId = std::string;

constexpr std::size_t EXISTING_RESSOURCES = 7;

enum class Resource : std::int8_t {
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
    Tile() = default;

    explicit Tile(Position position);

    [[nodiscard]] Position getPosition() const;

    [[nodiscard]] const std::unordered_map<Resource, int> &getResources() const;

    void setResources(const std::unordered_map<Resource, int> &resources);

    void addResources(const std::unordered_map<Resource, int> &resources);

    bool hasResource(const Resource &resource) const;

    void takeResource(const Resource &resource);

    void dropResource(const Resource &resource);

private:
    Position _position;
    std::unordered_map<Resource, int> _resources;
};
}

#endif

/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <list>
    #include <string>
    #include <utility>
    #include <sys/types.h>
    #include <unordered_map>
    #include <cstdint>
    #include "Player.hpp"
    #include "Resources.hpp"

namespace zappy::server {

class Map {
public:
    using Tile = zappy::data::Tile;
    using Position = zappy::data::Position;

    Map(std::uint32_t width, std::list<Tile> tiles, std::uint32_t height)
    : _width(width), _height(height), _tiles(std::move(tiles)) {}
    ~Map() = default;

    [[nodiscard]] std::uint32_t getWidth() const;
    [[nodiscard]] std::uint32_t getHeight() const;
    [[nodiscard]] const Tile &getTile(const Position &pos) const;
    [[nodiscard]] const Player &getPlayer(const PlayerId &id) const;
    void generateResources();
    bool takeResource(Resource resource, Position pos);
    void dropResource(Resource resource, Position pos);

private:
    std::uint32_t _width;
    std::uint32_t _height;
    std::list<Tile> _tiles;
    std::unordered_map<PlayerId, Player> _players;
};

}

#endif

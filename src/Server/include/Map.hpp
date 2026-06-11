/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

#include <list>
#include <utility>
#include <sys/types.h>

// Temp
class Tile {};
struct Position {
    uint x;
    uint y;
};
class Player {};
using PlayerId = uint;
class Resource {};

namespace zappy::server {

class Map {
public:
    Map(uint width, std::list<Tile> tiles, uint height)
    : _width(width), _height(height), _tiles(std::move(tiles)) {}
    ~Map() = default;

    [[nodiscard]] uint getWidth() const;
    [[nodiscard]] uint getHeight() const;
    [[nodiscard]] Tile getTile(Position &pos) const;
    [[nodiscard]] Player getPlayer(PlayerId id) const;
    void generateResources();
    bool takeResource(Resource resource, Position pos);
    void dropResource(Resource resource, Position pos);

private:
    uint _width;
    uint _height;
    std::list<Tile> _tiles;
};

}
#endif
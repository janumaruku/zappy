/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "Map.hpp"
#include <stdexcept>
#include <iterator>

namespace zappy::server {

uint Map::getWidth() const
{
    return this->_width;
}

uint Map::getHeight() const
{
    return this->_height;
}

const Map::Tile &Map::getTile(const Position &pos) const
{
    if (pos.x >= _width || pos.y >= _height)
        throw std::out_of_range("Position out of map bounds");

    const std::size_t index = (static_cast<std::size_t>(pos.y) * _width) + pos.x;

    auto it = _tiles.begin();
    std::advance(it, static_cast<std::ptrdiff_t>(index));
    return *it;
}

const Player &Map::getPlayer(const PlayerId &id) const
{
    return _players.at(id);
}

}
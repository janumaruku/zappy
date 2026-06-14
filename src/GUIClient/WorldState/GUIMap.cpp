/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.cpp
*/

#include "GUIMap.hpp"

#include <algorithm>
#include <iostream>

namespace zappy::gui {
GUIMap::GUIMap(const uint &width, const uint &height): _width(width),
    _height(height)
{

}

uint GUIMap::getWidth() const
{
    return _width;
}

uint GUIMap::getHeight() const
{
    return _height;
}

data::Tile &GUIMap::getTile(data::Position pos)
{
    if (pos.getX() > static_cast<int>(_width) || pos.getX() < 0 ||
        pos.getY() > static_cast<int>(_height) || pos.getY() < 0) {
        throw std::runtime_error("getTile position out of bound");
    }
    for (auto &it: _tiles) {
        if (it.getPosition() == pos) {
            return it;
        }
    }
    const data::Tile newPositionTile(pos);
    _tiles.push_back(newPositionTile);
    return _tiles.back();
}

void GUIMap::updateTile(const data::Position pos,
    const std::map<data::Resource, uint> &resources)
{
    for (const auto &it: resources) {
        getTile(pos).getResources().insert_or_assign(it.first, it.second);
    }
}
}

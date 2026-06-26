/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.cpp
*/

#include "GUIMap.hpp"

#include <iostream>

namespace zappy::gui {
GUIMap::GUIMap(const int &width, const int &height): _width(width),
    _height(height)
{
    _tiles.resize(_width * _height);
}

int GUIMap::getWidth() const
{
    return _width;
}

int GUIMap::getHeight() const
{
    return _height;
}

const data::Tile &GUIMap::getTile(data::Position pos) const
{
    if (pos.getX() >= _width || pos.getX() < 0 ||
        pos.getY() >= _height || pos.getY() < 0) {
        throw std::runtime_error("getTile position out of bound");
    }

    const auto index = (pos.getY() * _width) + pos.getX();

    return _tiles[index];
}

data::Tile &GUIMap::getTile(data::Position pos)
{
    if (pos.getX() >= _width || pos.getX() < 0 ||
        pos.getY() >= _height || pos.getY() < 0) {
        throw std::runtime_error("getTile position out of bound");
    }

    const auto index = (pos.getY() * _width) + pos.getX();

    return _tiles[index];
}

void GUIMap::updateWidth(const int width)
{
    _width = width;
    _tiles.resize(_width * _height);
}

void GUIMap::updateHeight(const int height)
{
    _height = height;
    _tiles.resize(_width * _height);
}

void GUIMap::updateTile(const data::Position pos,
    const std::unordered_map<data::Resource, int> &resources)
{
    if (pos.getX() >= _width || pos.getX() < 0 ||
        pos.getY() >= _height || pos.getY() < 0) {
        throw std::runtime_error("getTile position out of bound");
    }

    const auto index = (pos.getY() * _width) + pos.getX();

    _tiles[index].addResources(resources);
}
}

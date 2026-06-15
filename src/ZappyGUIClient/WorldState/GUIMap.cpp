/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.cpp
*/

#include "GUIMap.hpp"

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

const data::Tile &GUIMap::getTile(data::Position pos) const
{
    if (pos.getX() > static_cast<int>(_width) || pos.getX() < 0 ||
        pos.getY() > static_cast<int>(_height) || pos.getY() < 0) {
        throw std::runtime_error("getTile position out of bound");
    }

    const auto index = (pos.getY() * _width) + pos.getX();

    return _tiles[index];
}

void GUIMap::updateWidth(const uint width)
{
    _width = width;
}

void GUIMap::updateHeight(const uint height)
{
    _height = height;
}

void GUIMap::updateTile(const data::Position pos,
    const std::unordered_map<data::Resource, uint> &resources)
{
    if (pos.getX() > static_cast<int>(_width) || pos.getX() < 0 ||
        pos.getY() > static_cast<int>(_height) || pos.getY() < 0) {
        throw std::runtime_error("getTile position out of bound");
    }

    const auto index = (pos.getY() * _width) + pos.getX();

    _tiles[index].setResources(resources);
}
}

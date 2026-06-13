/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.hpp
*/

#ifndef GUIMAP_HPP
#define GUIMAP_HPP
#include <sys/types.h>

#include "Tile.hpp"

namespace zappy::gui {
class GUIMap {
public:

    GUIMap() = default;
    GUIMap(const uint &width, const uint &height);

    [[nodiscard]] uint getWidth() const;

    [[nodiscard]] uint getHeight() const;

    data::Tile &getTile(data::Position pos);

    void updateTile(data::Position pos,
        const std::map<data::Resource, uint> &resources);

private:
    uint _width = 0;
    uint _height = 0;
    std::list<data::Tile> _tiles;
};
}

#endif

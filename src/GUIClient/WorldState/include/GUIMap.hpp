/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.hpp
*/

#ifndef GUIMAP_HPP
#define GUIMAP_HPP
#include <vector>
#include <sys/types.h>

#include "Tile.hpp"

namespace zappy::gui {
class GUIMap {
public:
    GUIMap(const uint &width, const uint &height);

    [[nodiscard]] uint getWidth() const;

    [[nodiscard]] uint getHeight() const;

    [[nodiscard]] const data::Tile &getTile(data::Position pos) const;

    void updateTile(data::Position pos,
        const std::unordered_map<data::Resource, uint> &resources);

    void generate();

private:
    uint _width = 0;
    uint _height = 0;
    std::vector<data::Tile> _tiles;
};
}

#endif

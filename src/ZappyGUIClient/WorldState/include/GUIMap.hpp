/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIMap.hpp
*/

#ifndef GUIMAP_HPP
#define GUIMAP_HPP
#include <vector>

#include "Tile.hpp"

namespace zappy::gui {
class GUIMap {
public:
    GUIMap() = default;

    GUIMap(const int &width, const int &height);

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] const data::Tile &getTile(data::Position pos) const;

    void updateWidth(int width);

    void updateHeight(int height);

    void updateTile(data::Position pos,
        const std::unordered_map<data::Resource, int> &resources);

private:
    int _width = 0;
    int _height = 0;
    std::vector<data::Tile> _tiles;
};
}

#endif

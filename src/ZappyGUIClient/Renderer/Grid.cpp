/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Grid
*/

#include "Grid.hpp"

#include <raylib.h>

#include "ResourceManager.hpp"

namespace zappy::gui {
Grid::Grid(const int &width, const int &height): _width(width), _height(height)
{
}

void Grid::render() const
{
    for (auto y = 0; y < _height; ++y) {
        for (auto x = 0; x < _width; ++x) {
            DrawRectangle((x * TILE_SIZE) + GRID_SIZE,
                (y * TILE_SIZE) + GRID_SIZE, TILE_SIZE - GRID_SIZE,
                TILE_SIZE - GRID_SIZE, WHITE);
        }
    }

}
}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ResourceManager
*/

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include <raylib.h>
#include <string>
#include <vector>

#include "ARenderManager.hpp"
#include "Position.hpp"

namespace zappy::gui {

constexpr int TILE_SIZE = 50;

constexpr int CELL_SIZE = TILE_SIZE / 3;

constexpr int RESOURCE_RADIUS = TILE_SIZE / 6;

constexpr int PLAYER_RADIUS = TILE_SIZE / 4;

constexpr int GRID_SIZE = 3;

const std::string PLAYER_SPRITE_PATH = "src/resources/testSprite.png";

struct TextureData {
    std::string name;
    int x;
    int y;
    Color color;
};

const std::vector<TextureData> RESOURCE_DATA = {
    {.name = "food", .x = 0, .y = 0, .color = RED},
    {.name = "linemate", .x = 1, .y = 0, .color = LIME},
    {.name = "deraumere", .x = 2, .y = 0, .color = BLUE},
    {.name = "sibur", .x = 0, .y = 1, .color = YELLOW},
    {.name = "mendiane", .x = 2, .y = 1, .color = VIOLET},
    {.name = "phiras", .x = 0, .y = 2, .color = ORANGE},
    {.name = "thystame", .x = 1, .y = 2, .color = BROWN},
};

const std::vector<std::pair<std::string, int16_t>> PLAYER_DIRECTION_DATA{
    {"player_north", -90},
    {"player_east", 0},
    {"player_south", 90},
    {"player_west", 180},
};

class ResourceManager: public designPattern::ARenderManager {
public:
    ResourceManager();
    ~ResourceManager() override = default;

protected:
    void loadImages() override;
    void loadRectangles() override;

    [[nodiscard]] static Image createImageResource(data::Position offset,
        int radius, Color color);
};
} // namespace zappy::gui

#endif // RESOURCEMANAGER_HPP

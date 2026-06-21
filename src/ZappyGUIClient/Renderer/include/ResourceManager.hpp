/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ResourceManager
*/

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP
#include <map>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

#include "Position.hpp"

namespace zappy::gui {

constexpr int TILE_SIZE = 50;
constexpr int CELL_SIZE = TILE_SIZE / 3;
constexpr int RESOURCE_RADIUS = TILE_SIZE / 6;
constexpr int PLAYER_RADIUS = TILE_SIZE / 4;
constexpr int GRID_SIZE = 3;

const std::string PLAYER_SPRITE_PATH = "src/resources/testSprite.png";

struct ResourcesData {
    std::string name;
    data::Position pos;
    Color color;
};

const std::vector<ResourcesData> RESOURCE_DATA = {
    {.name = "food", .pos = {0, 0}, .color = RED},
    {.name = "linemate", .pos = {1, 0}, .color = LIME},
    {.name = "deraumere", .pos = {2, 0}, .color = BLUE},
    {.name = "sibur", .pos = {0, 1}, .color = YELLOW},
    {.name = "mendiane", .pos = {2, 1}, .color = VIOLET},
    {.name = "phiras", .pos = {0, 2}, .color = ORANGE},
    {.name = "thystame", .pos = {1, 2}, .color = BROWN},
};

const std::vector<std::pair<std::string, int16_t>> PLAYER_DIRECTION_DATA {
    {"player_north", -90},
    {"player_east", 0},
    {"player_south", 90},
    {"player_west", 180},
};

class ResourceManager {
public:
    ResourceManager();

    ~ResourceManager();

    void loadTextures();

    const Texture2D &getTexture(const std::string &name) const;

private:
    std::unordered_map<std::string, Image> _images;
    std::unordered_map<std::string, Texture2D> _textures;

    void loadImages();

    [[nodiscard]] static Image createImageResource(data::Position offset,
        int radius,Color color);
    static Image createImageFromFile(const std::string &filePath);

};
}

#endif //RESOURCEMANAGER_HPP

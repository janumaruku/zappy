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
#include <unordered_map>
#include <vector>

#include "Position.hpp"

namespace zappy::gui {

constexpr int TILE_SIZE = 50;
constexpr int CELL_SIZE = TILE_SIZE / 3;
constexpr int RESOURCE_RADIUS = TILE_SIZE / 6;
constexpr int GRID_SIZE = 3;

const std::vector<std::string> RESOURCE_NAMES = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame",
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
        int radius,
        Color color);

};
}

#endif //RESOURCEMANAGER_HPP

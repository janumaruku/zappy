/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ResourceManager
*/

#include "ResourceManager.hpp"

#include <format>
#include <stdexcept>

namespace zappy::gui {
ResourceManager::ResourceManager()
{
    loadTextures();
}

ResourceManager::~ResourceManager()
{
    for (const auto &it: _textures) {
        UnloadTexture(it.second);
    }
}

void ResourceManager::loadTextures()
{
    loadImages();
    for (const auto &it: _images) {
        _textures.insert({it.first, LoadTextureFromImage(it.second)});
    }
}

const Texture2D &ResourceManager::getTexture(const std::string &name) const
{
    if (_textures.contains(name)) {
        return _textures.at(name);
    }
    throw std::out_of_range(std::format("Texture {} not found", name));
}

void ResourceManager::loadImages()
{
    auto insertImage = [this](const std::string &name,
        const data::Position &pos, const int &radius, const Color &c) {
        _images.insert({name, createImageResource(pos, radius, c)});
    };
    insertImage("food", {0, 0}, RESOURCE_RADIUS, RED);
    insertImage("linemate", {CELL_SIZE, 0}, RESOURCE_RADIUS, LIME);
    insertImage("deraumere", {CELL_SIZE * 2, 0}, RESOURCE_RADIUS,BLUE);
    insertImage("sibur", {0, CELL_SIZE}, RESOURCE_RADIUS, YELLOW);
    insertImage("egg", {CELL_SIZE, CELL_SIZE}, RESOURCE_RADIUS,BLACK);
    insertImage("mendiane", {CELL_SIZE * 2, CELL_SIZE}, RESOURCE_RADIUS,VIOLET);
    insertImage("phiras", {0, CELL_SIZE * 2}, RESOURCE_RADIUS,ORANGE);
    insertImage("thystame", {CELL_SIZE, CELL_SIZE * 2}, RESOURCE_RADIUS, BROWN);
    _images.insert({"tile", GenImageColor(TILE_SIZE, TILE_SIZE, GRAY)});
}

Image ResourceManager::createImageResource(const data::Position offset,
    const int radius, const Color color)
{
    Image imageResource = GenImageColor(TILE_SIZE, TILE_SIZE, BLANK);
    ImageDrawCircle(&imageResource, offset.getX() + radius,
        offset.getY() + radius, radius, color);
    return imageResource;
}
}

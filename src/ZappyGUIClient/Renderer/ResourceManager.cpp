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
    for (const auto &it: RESOURCE_DATA) {
        data::Position position = {(it.pos.getX() * CELL_SIZE) + GRID_SIZE,
            (it.pos.getY() * CELL_SIZE) + GRID_SIZE};
        insertImage(it.name, position, RESOURCE_RADIUS, it.color);
    }

    insertImage("egg", {CELL_SIZE, CELL_SIZE}, RESOURCE_RADIUS, BLACK);
    _images.insert({"tile", GenImageColor(TILE_SIZE, TILE_SIZE, GRAY)});

    for (const auto &it: PLAYER_DIRECTION_DATA) {
        Image imagePlayer = createImageFromFile(PLAYER_SPRITE_PATH);
        ImageRotate(&imagePlayer, it.second);
        _images.insert({it.first, imagePlayer});
    }
}

Image ResourceManager::createImageResource(const data::Position offset,
    const int radius, const Color color)
{
    Image imageResource = GenImageColor(TILE_SIZE, TILE_SIZE, BLANK);
    ImageDrawCircle(&imageResource, offset.getX() + radius,
        offset.getY() + radius, radius, color);
    return imageResource;
}

Image ResourceManager::createImageFromFile(const std::string &filePath)
{
    const Image image = LoadImage(filePath.c_str());
    if (!IsImageValid(image)) {
        throw std::invalid_argument("Path to load image not found");
    }
    return image;
}
} // namespace zappy::gui

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ResourceManager
*/

#include "ResourceManager.hpp"

#include <format>

namespace zappy::gui {

ResourceManager::ResourceManager()
{
    ARenderManager::loadTextures();
}

void ResourceManager::loadImages()
{
    auto insertImage = [this](const std::string &name,
    const data::Position &pos, const int &radius, const Color &c) {
        _images.insert({name, createImageResource(pos, radius, c)});
    };
    for (const auto &it: RESOURCE_DATA) {
        data::Position position = {(it.x * CELL_SIZE) + GRID_SIZE,
            (it.y * CELL_SIZE) + GRID_SIZE};
        insertImage(it.name, position, RESOURCE_RADIUS, it.color);
    }

    _images.insert({"tile", GenImageColor(TILE_SIZE, TILE_SIZE, GRAY)});

    for (const auto &it: PLAYER_DIRECTION_DATA) {
        Image imagePlayer = createImageFromFile(PLAYER_SPRITE_PATH);
        ImageRotate(&imagePlayer, it.second);
        _images.insert({it.first, imagePlayer});
    }

    Image imageEgg = createImageFromFile(EGG_SPRITE_PATH);
    _images.insert({"egg", imageEgg});
}

void ResourceManager::loadRectangles()
{

}

Image ResourceManager::createImageResource(const data::Position offset,
    const int radius, const Color color)
{
    Image imageResource = GenImageColor(TILE_SIZE, TILE_SIZE, BLANK);
    ImageDrawCircle(&imageResource, offset.getX() + radius,
        offset.getY() + radius, radius, color);
    return imageResource;
}
} // namespace zappy::gui

/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** ARenderManager
*/

#include "include/ARenderManager.hpp"

#include <format>
#include <iostream>
#include <stdexcept>

namespace designPattern {

ARenderManager::~ARenderManager()
{
    for (const auto &it: _textures) {
        UnloadTexture(it.second);
    }
}

void ARenderManager::loadTextures()
{
    loadRectangles();
    loadImages();
    for (const auto &it: _images) {
        if (!IsImageValid(it.second)) {
            std::cerr << "Invalid image: " << it.first << std::endl;
            continue;
        }
        Texture2D texture = LoadTextureFromImage(it.second);
        if (!IsTextureValid(texture)) {
            std::cerr << "Failed to load texture: " << it.first << std::endl;
            continue;
        }

        _textures.insert({it.first, texture});
    }
}

const Texture2D &ARenderManager::getTexture(const std::string &name) const
{
    if (_textures.contains(name)) {
        return _textures.at(name);
    }
    throw std::out_of_range(std::format("Texture {} not found", name));
}

Texture2D &ARenderManager::getTexture(const std::string &name)
{
    if (_textures.contains(name)) {
        return _textures.at(name);
    }
    throw std::out_of_range(std::format("Texture {} not found", name));
}

const Rectangle &ARenderManager::getRectangle(const std::string &name) const
{
    if (_rectangles.contains(name)) {
        return _rectangles.at(name);
    }
    throw std::out_of_range(std::format("Rectangle {} not found", name));
}

void ARenderManager::createRectangle(std::string name, const Vector2 &position,
    const int &width, const int &height)
{
    Rectangle rec = {position.x, position.y, static_cast<float>(width),
        static_cast<float>(height)};

    _rectangles.insert({name, rec});
}

Image ARenderManager::createImageFromFile(const std::string &filePath)
{
    const Image image = LoadImage(filePath.c_str());
    if (!IsImageValid(image)) {
        throw std::invalid_argument("Path to load image not found");
    }
    return image;
}
} // namespace designPattern

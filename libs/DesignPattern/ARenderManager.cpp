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

        _textures.insert({it.first, LoadTextureFromImage(it.second)});
    }
}

const Texture2D &ARenderManager::getTexture(const std::string &name) const
{
    if (_textures.contains(name)) {
        return _textures.at(name);
    }
    throw std::out_of_range(std::format("Texture {} not found", name));
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

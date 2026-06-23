/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** ARenderManager
*/

#ifndef ARENDERMANAGER_HPP
#define ARENDERMANAGER_HPP
#include <raylib.h>
#include <string>
#include <unordered_map>

#include "IRenderManager.hpp"

namespace designPattern {
class ARenderManager: public IRenderManager {
public:
    ARenderManager() = default;
    ~ARenderManager() override;

    void loadTextures() override;

    const Texture2D &getTexture(const std::string &name) const override;

    const Rectangle &getRectangle(const std::string &name) const override;

    void createRectangle(std::string name, const Vector2 &position,
        const int &width, const int &height) override;

protected:
    std::unordered_map<std::string, Image> _images;
    std::unordered_map<std::string, Texture2D> _textures;
    std::unordered_map<std::string, Rectangle> _rectangles;

    Image createImageFromFile(const std::string &filePath) override;
};
} // namespace designPattern

#endif // ARENDERMANAGER_HPP

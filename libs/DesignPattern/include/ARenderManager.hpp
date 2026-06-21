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

protected:
    std::unordered_map<std::string, Image> _images;
    std::unordered_map<std::string, Texture2D> _textures;

    Image createImageFromFile(const std::string &filePath) override;
};
} // namespace designPattern

#endif // ARENDERMANAGER_HPP

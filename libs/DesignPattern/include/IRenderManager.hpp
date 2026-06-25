/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** ARenderManager
*/

#ifndef IRENDERMANAGER_HPP
#define IRENDERMANAGER_HPP

namespace designPattern {
class IRenderManager {
public:
    virtual ~IRenderManager() = default;

    virtual void loadTextures() = 0;

    virtual const Texture2D &getTexture(const std::string &name) const = 0;

    virtual Texture2D &getTexture(const std::string &name) = 0;

    virtual const Rectangle &getRectangle(const std::string &name) const = 0;

    virtual void createRectangle(std::string name, const Vector2 &position,
        const int &width, const int &height) = 0;

protected:
    virtual void loadImages()     = 0;
    virtual void loadRectangles() = 0;

    virtual Image createImageFromFile(const std::string &filePath) = 0;
};
} // namespace designPattern

#endif // IRENDERMANAGER_HPP

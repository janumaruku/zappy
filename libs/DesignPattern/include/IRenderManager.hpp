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
    virtual ~IRenderManager()   = default;
    virtual void loadTextures() = 0;
    [[nodiscard]] virtual const Texture2D &getTexture(const std::string &name)
        const = 0;

protected:
    virtual void loadImages()                                      = 0;
    virtual Image createImageFromFile(const std::string &filePath) = 0;
};
} // namespace designPattern

#endif // IRENDERMANAGER_HPP

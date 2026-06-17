/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer.hpp
*/

#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <map>
#include <string>

#include "raylib.h"
#include "WorldState.hpp"

namespace zappy::gui {

class Renderer {
    const int TILE_SIZE = 50;

public:
    Renderer();

    ~Renderer();

    void loadTextures();

    void render(const WorldState &world) const;

    bool isWindowOpen();

private:
    static void renderMap(const GUIMap &map);

    static void renderPlayers(const std::map<data::PlayerId, GUIPlayer>
        &players);

    static void renderEggs(const std::map<unsigned int, data::Egg> &eggs);

    static void updateAnimation(const GUIPlayer &player);

    Vector2 tileToPixel(data::Position pos) const;

    Image createImageResource(Color color) const;

    void loadImages();

    std::unordered_map<std::string, Image> _images;
    std::map<std::string, Texture2D> _textures;
    // std::map<data::PlayerId, Animation> _animations;
    Camera2D _camera;
};
} // namespace zappy::gui
#endif // RENDERER_HPP

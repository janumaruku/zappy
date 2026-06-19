/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer.hpp
*/

#ifndef RENDERER_HPP
#define RENDERER_HPP
#include <map>
#include <memory>
#include <string>

#include "Grid.hpp"
#include "raylib.h"
#include "ResourceManager.hpp"
#include "WorldState.hpp"
#include "Grid.hpp"

namespace zappy::gui {

constexpr int WINDOW_WIDTH  = 800;
constexpr int WINDOW_HEIGHT = 600;
class Renderer {
public:
    Renderer(const int &width, const int &height);

    ~Renderer();

    void render(const WorldState &world);

    bool isWindowOpen();

private:
    void renderMap(const GUIMap &map) const;

    void renderResourcesFromTile(std::unordered_map<data::Resource, int> tile,
        data::Position position) const;

    static void renderPlayers(const std::unordered_map<data::PlayerId, GUIPlayer>
            &players);

    static void renderEggs(const std::map<unsigned int, data::Egg> &eggs);

    static void updateAnimation(const GUIPlayer &player);

    void updateCamera();
    void updateZoom(const float &wheel);
    void updateCameraMovement();

    [[nodiscard]] static Vector2 tileToPixel(data::Position pos);

    static std::string resourceToString(const data::Resource &resource);
    // std::map<data::PlayerId, Animation> _animations;
    Grid _grid;
    Camera2D _camera;
    std::unique_ptr<ResourceManager> _resourceManager;
};
} // namespace zappy::gui
#endif // RENDERER_HPP

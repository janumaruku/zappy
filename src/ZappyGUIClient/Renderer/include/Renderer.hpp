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

#include "raylib.h"
#include "ResourceManager.hpp"
#include "WorldState.hpp"
#include "Grid.hpp"

namespace zappy::gui {

class Renderer {

public:
    Renderer(const int &width, const int &height);

    ~Renderer();

    void render(const WorldState &world) const;

    bool isWindowOpen();

private:
    void renderMap(const GUIMap &map) const;

    static std::string resourceToString(const data::Resource &resource);

    void renderResourcesFromTile(std::unordered_map<data::Resource, int> tile,
        data::Position position) const;

    static void renderPlayers(const std::map<data::PlayerId, GUIPlayer>
        &players);

    static void renderEggs(const std::map<unsigned int, data::Egg> &eggs);

    static void updateAnimation(const GUIPlayer &player);

    [[nodiscard]] Vector2 tileToPixel(data::Position pos) const;

    // std::map<data::PlayerId, Animation> _animations;
    Grid _grid;
    Camera2D _camera;
    std::unique_ptr<ResourceManager> _resourceManager;
};
} // namespace zappy::gui
#endif // RENDERER_HPP

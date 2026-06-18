/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include <iostream>

#include "Renderer.hpp"
#include "ResourceManager.hpp"

namespace zappy::gui {
Renderer::Renderer(const int &width, const int &height): _grid(width, height),
    _camera({
        .offset = Vector2{.x = 0.0F, .y = 0.0F},
        .target = Vector2{.x = 0.0F, .y = 0.0F},
        .rotation = 0.0F,
        .zoom = 1.0F})
{
    InitWindow(800, 600, "Zappy - Renderer");
    SetTargetFPS(60);
    _resourceManager = std::make_unique<ResourceManager>();
}

Renderer::~Renderer()
{
    CloseWindow();
}

void Renderer::render(const WorldState &world) const
{
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(_camera);
    renderMap(world.getMap());
    EndMode2D();
    EndDrawing();
}

bool Renderer::isWindowOpen() // NOLINT
{
    return !WindowShouldClose();
}

void Renderer::renderMap(const GUIMap &map) const
{
    _grid.render();
    const auto width = map.getWidth();
    const auto len = map.getWidth() * map.getHeight();

    auto y = 0;
    for (auto x = 0; x < len; ++x) {
        if (x == width - 1)
            ++y;
        auto tile = map.getTile({x % width, y}).getResources();

        for (auto const &[name, count]: tile) {
            auto resourceTexture = _resourceManager->getTexture(
                resourceToString(name));
            DrawTexture(resourceTexture, (x % width) * TILE_SIZE, y * TILE_SIZE,
                WHITE);
        }
    }
}

std::string Renderer::resourceToString(const data::Resource &resource)
{
    return RESOURCE_DATA[static_cast<int>(resource)].name;
}

void Renderer::renderPlayers(const std::map<data::PlayerId, GUIPlayer> &players)
{
    (void)players;
}

void Renderer::renderEggs(const std::map<unsigned int, data::Egg> &eggs)
{
    (void)eggs;
}

void Renderer::updateAnimation(const GUIPlayer &player)
{
    (void)player;
}

Vector2 Renderer::tileToPixel(const data::Position pos) const
{
    return {.x = static_cast<float>(pos.getX() * TILE_SIZE),
            .y = static_cast<float>(pos.getY() * TILE_SIZE)};
}

} // namespace zappy::gui

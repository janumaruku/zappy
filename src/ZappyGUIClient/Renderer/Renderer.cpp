/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace zappy::gui {
Renderer::Renderer():
    _camera({.offset = Vector2{.x = 0.0F, .y = 0.0F},
        .target      = Vector2{.x = 400.0F, .y = 300.0F},
        .rotation    = 0.0F,
        .zoom        = 1.0F})
{
    InitWindow(800, 600, "Zappy - Renderer");
    SetTargetFPS(60);
}

Renderer::~Renderer()
{
    CloseWindow();
}

void Renderer::loadTextures()
{}

void Renderer::render(const WorldState &world) const
{
    (void)world;
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(_camera);
    EndMode2D();
    EndDrawing();
}

bool Renderer::isWindowOpen() // NOLINT
{
    return !WindowShouldClose();
}

void Renderer::renderMap(const GUIMap &map)
{
    (void)map;
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
    return {pos.getX() * TILE_SIZE, pos.getY() * TILE_SIZE};
}
} // namespace zappy::gui

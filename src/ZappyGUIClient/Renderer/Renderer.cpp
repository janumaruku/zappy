/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include "Renderer.hpp"

namespace zappy::gui {
Renderer::Renderer(): _camera({.offset = Vector2{.x = 0.0F, .y = 0.0F},
                               .target = Vector2{.x = 400.0F, .y = 300.0F},
                               .rotation = 0.0F,
                               .zoom = 1.0F})
{
    InitWindow(800, 600, "Zappy - Renderer");
    SetTargetFPS(60);
}

Renderer::~Renderer()
{
    for (auto &it: _textures) {
        UnloadTexture(it.second);
    }
    CloseWindow();
}

Image Renderer::createImageResource(const Color color) const
{
    Image imageResource = GenImageColor(TILE_SIZE, TILE_SIZE, BLANK);
    ImageDrawCircle(&imageResource, 25, 25, 15, color);
    return imageResource;
}

void Renderer::loadImages()
{
    std::unordered_map<std::string, Image> images;

    _images.insert({"tile", GenImageColor(TILE_SIZE, TILE_SIZE, GRAY)});

    _images.insert({"food", createImageResource(RED)});
    _images.insert({"linemate", createImageResource(LIME)});
    _images.insert({"deraumere", createImageResource(BLUE)});
    _images.insert({"sibur", createImageResource(YELLOW)});
    _images.insert({"mendiane", createImageResource(VIOLET)});
    _images.insert({"phiras", createImageResource(ORANGE)});
    _images.insert({"thystame", createImageResource(BROWN)});
}

void Renderer::loadTextures()
{
    loadImages();
    for (const auto &it: _images) {
        _textures.insert({it.first, LoadTextureFromImage(it.second)});
    }
}

void Renderer::render(const WorldState &world) const
{
    (void)world;
    BeginDrawing();
    ClearBackground(RAYWHITE);

    //DrawTexture(_textures.at("food"), 50, 50, WHITE);
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
    return {.x = static_cast<float>(pos.getX() * TILE_SIZE),
            .y = static_cast<float>(pos.getY() * TILE_SIZE)};
}
} // namespace zappy::gui

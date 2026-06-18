/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include "Renderer.hpp"

#include <algorithm>
#include <cmath>

#include "ResourceManager.hpp"

namespace zappy::gui {
Renderer::Renderer(const int &width, const int &height): _grid(width, height),
    _camera({
        .offset = Vector2{
            WINDOW_WIDTH / 2,
            WINDOW_HEIGHT / 2
        },
        .target = Vector2{
            static_cast<float>((width * TILE_SIZE) / 2),
            static_cast<float>((height * TILE_SIZE) / 2)
        },
        .rotation   = 0.0F,
        .zoom       = 1.0F})
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Zappy - Renderer");
    SetTargetFPS(60);
    _resourceManager = std::make_unique<ResourceManager>();
}

Renderer::~Renderer()
{
    _resourceManager.reset();
    CloseWindow();
}

void Renderer::render(const WorldState &world)
{
    updateCamera();
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
    const auto len   = map.getWidth() * map.getHeight();

    auto y = 0;
    for (auto x = 0; x < len; ++x) {
        if (x == width - 1)
            ++y;
        auto tile = map.getTile({x % width, y}).getResources();

        renderResourcesFromTile(tile, {(x % width), y});
    }
}

void Renderer::renderResourcesFromTile(std::unordered_map<data::Resource, int>
                                           tile,
    const data::Position position) const
{

    for (auto const &[name, count]: tile) {
        auto resourceTexture =
            _resourceManager->getTexture(resourceToString(name));
        if (count > 0)
            DrawTexture(resourceTexture, position.getX() * TILE_SIZE,
                position.getY() * TILE_SIZE, WHITE);
    }
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
void Renderer::updateCamera()
{
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), _camera);
        _camera.offset = GetMousePosition();
        _camera.target = mouseWorldPos;
        float scale = 0.2f * wheel;
        _camera.zoom =
            std::clamp(std::expf(logf(_camera.zoom) + scale), 0.2f, 3.0f);
    }
}

Vector2 Renderer::tileToPixel(const data::Position pos) const
{
    return {.x = static_cast<float>(pos.getX() * TILE_SIZE),
        .y     = static_cast<float>(pos.getY() * TILE_SIZE)};
}

std::string Renderer::resourceToString(const data::Resource &resource)
{
    return RESOURCE_DATA[static_cast<int>(resource)].name;
}

} // namespace zappy::gui

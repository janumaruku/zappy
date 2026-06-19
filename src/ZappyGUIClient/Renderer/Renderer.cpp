/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include "Renderer.hpp"

#include <algorithm>
#include <cmath>

#include "raymath.h"
#include "ResourceManager.hpp"

namespace zappy::gui {
Renderer::Renderer(const int &width, const int &height,
    const SubjectList &list):
    AObserver{list}, _grid(width, height),
    _camera({
        .offset = Vector2{
            WINDOW_WIDTH / 2,
            WINDOW_HEIGHT / 2
        },
        .target = Vector2{
            static_cast<float>((width * TILE_SIZE) / 2),
            static_cast<float>((height * TILE_SIZE) / 2)
        },
        .rotation = 0.0F,
        .zoom = 1.0F})
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
    renderPlayers(world.getPlayers());
    EndMode2D();
    EndDrawing();
}

bool Renderer::isWindowOpen() // NOLINT
{
    return !WindowShouldClose();
}

void Renderer::onNotify(const ZappyEvent &event)
{
    (void)event;
    std::visit(OnEvent{*this}, event);
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
        const auto tile = map.getTile({x % width, y}).getResources();

        renderResourcesFromTile(tile, {(x % width), y});
    }
}

void Renderer::renderResourcesFromTile(std::unordered_map<data::Resource, int>
    tile,
    const data::Position position) const
{

    for (auto const &[name, count]: tile) {
        const auto resourceTexture =
            _resourceManager->getTexture(resourceToString(name));
        if (count > 0) {
            DrawTexture(resourceTexture, position.getX() * TILE_SIZE,
                position.getY() * TILE_SIZE, WHITE);
        }
    }
}

void Renderer::renderPlayers(
    const std::unordered_map<data::PlayerId, GUIPlayer> &players)
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
    const float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        updateZoom(wheel);
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        updateCameraMovement();
    }
}

void Renderer::updateZoom(const float &wheel)
{
    _camera.offset = GetMousePosition();
    _camera.target = GetScreenToWorld2D(GetMousePosition(), _camera);
    const float scale = 0.2f * wheel;
    _camera.zoom = Clamp(expf(logf(_camera.zoom) + scale), 0.2f, 3.0f);
}

void Renderer::updateCameraMovement()
{
    const Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0f / _camera.zoom);
    _camera.target = Vector2Add(_camera.target, delta);
}

Vector2 Renderer::tileToPixel(const data::Position pos)
{
    return {
        .x = static_cast<float>(pos.getX() * TILE_SIZE),
        .y = static_cast<float>(pos.getY() * TILE_SIZE)
    };
}

std::string Renderer::resourceToString(const data::Resource &resource)
{
    return RESOURCE_DATA[static_cast<int>(resource)].name;
}

} // namespace zappy::gui

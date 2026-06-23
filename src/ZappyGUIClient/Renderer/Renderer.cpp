/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include "Renderer.hpp"

#include <algorithm>
#include <cmath>

#include "Hud.hpp"
#include "raymath.h"
#include "ResourceManager.hpp"

namespace zappy::gui {
Renderer::Renderer(const int &width, const int &height,
    const SubjectList &list, const WorldState& worldState):
    AObserver{list}, _grid(width, height),
    _camera({
        .offset = Vector2{
            .x=WINDOW_WIDTH / 2,
            .y=WINDOW_HEIGHT / 2
        },
        .target = Vector2{
            .x=static_cast<float>(width * TILE_SIZE) / 2,
            .y=static_cast<float>(height * TILE_SIZE) / 2
        },
        .rotation = 0.0F,
        .zoom = 1.0F})
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Zappy - Renderer");
    SetTargetFPS(60);
    _resourceManager = std::make_unique<ResourceManager>();
    _hudManager = std::make_unique<HUDManager>(worldState);
}

Renderer::~Renderer()
{
    _resourceManager.reset();
    _hudManager.reset();
    CloseWindow();
}

void Renderer::render(const WorldState &world)
{
    updateCamera();
    updateHud(world);
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(_camera);
    renderMap(world.getMap());

    renderPlayers(world.getPlayers(), world.getTeams());
    EndMode2D();
    _hud.draw(world, _hudManager);
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
    const auto len   = map.getWidth() * map.getHeight();

    auto y = 0;
    for (auto x = 0; x < len; ++x) {
        if (x == width - 1)
            ++y;
        const auto tile = map.getTile({x % width, y}).getResources();

        renderResourcesFromTile(tile, {(x % width), y});
    }
}

void Renderer::renderResourcesFromTile(const std::unordered_map<data::Resource, int>&
    tile, const data::Position position) const
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

void Renderer::renderPlayers(const std::unordered_map<data::PlayerId, GUIPlayer>
    &players, const std::unordered_map<std::string, Team> &teams) const
{
    for (const auto &it: players) {
        const auto resourceTexture =
            _resourceManager->getTexture(playerOrientationToString(it.second
                    .getOrientation()));
        const auto position = it.second.getPosition();
        DrawTexture(resourceTexture,
            (position.getX() * TILE_SIZE) +
                ((TILE_SIZE - resourceTexture.width) / 2),
            (position.getY() * TILE_SIZE) +
                ((TILE_SIZE - resourceTexture.height) / 2),
            teams.at(it.second.getTeam()).getColor());
    }
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
    _camera.offset    = GetMousePosition();
    _camera.target    = GetScreenToWorld2D(GetMousePosition(), _camera);
    const float scale = 0.2F * wheel;
    _camera.zoom      = Clamp(expf(logf(_camera.zoom) + scale), 0.2F, 3.0F);
}

void Renderer::updateCameraMovement()
{
    const Vector2 delta = Vector2Scale(GetMouseDelta(), -1.0F / _camera.zoom);
    _camera.target      = Vector2Add(_camera.target, delta);
}

void Renderer::updateHud(const WorldState& worldState)
{
    _hud.update(worldState, _hudManager);
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

std::string Renderer::playerOrientationToString(const data::Orientation
        &orientation)
{
    return PLAYER_DIRECTION_DATA[static_cast<int>(orientation)].first;
}

} // namespace zappy::gui

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

void Renderer::registerCreators()
{
    //_animationFactory.registerCreator<>(Vector2 key);
}

void Renderer::render(const WorldState &world)
{
    updateCamera();
    updateHud(world);
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(_camera);
    renderMap(world.getMap());
    renderEggs();
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

void Renderer::renderMap(const GUIMap &map)
{
    _grid.render();
    const auto width  = map.getWidth();
    const auto height = map.getHeight();

    for (auto y = 0; y < height; ++y) {
        for (auto x = 0; x < width; ++x) {
            const auto tile = map.getTile({x, y}).getResources();
            renderResourcesFromTile(tile, {x, y});
            renderIncantation({x, y});
        }
    }
}

void Renderer::renderResourcesFromTile(const std::unordered_map<data::Resource,
                                           int> &tile,
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

void Renderer::renderPlayers(const std::unordered_map<data::PlayerId, GUIPlayer>
                                 &players,
    const std::unordered_map<std::string, Team> &teams) const
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

void Renderer::renderEggs()
{
    for (const auto &it: _eggs) {
        const data::Position &eggPosition = it.second;

        const auto &eggTexture = _resourceManager->getTexture("egg");

        float centerX = (eggPosition.getX() * TILE_SIZE) + CELL_SIZE +
            (CELL_SIZE / 2.0f) - (eggTexture.width / 2.0f) + GRID_SIZE;
        float centerY = (eggPosition.getY() * TILE_SIZE) + CELL_SIZE +
            (CELL_SIZE / 2.0f) - (eggTexture.height / 2.0f) + GRID_SIZE;

        DrawTexture(eggTexture, centerX + GRID_SIZE, centerY, WHITE);
    }
}

void Renderer::renderIncantation(const data::Position position)
{
    const data::Position incantationPosition = {
        position.getX() * TILE_SIZE, position.getY() * TILE_SIZE};

    if (_incantations.contains(position)) {
        DrawRectangle(incantationPosition.getX(), incantationPosition.getY(),
            TILE_SIZE, TILE_SIZE, INCANTATION_COLOR);
    }

    if (_incantationsRes.contains(position)) {
        auto [result, addedTime] = _incantationsRes.at(position);

        const auto elapsed = std::chrono::duration_cast<
            std::chrono::milliseconds>(std::chrono::steady_clock::now() -
            addedTime);

        if (elapsed < INCANTATION_END_DURATION) {
            const Color overlayColor =
                result ? INCANTATION_SUCCESS_COLOR : INCANTATION_FAILURE_COLOR;
            DrawRectangle(incantationPosition.getX(), incantationPosition.getY(),
                TILE_SIZE, TILE_SIZE, overlayColor);
        } else {
            _incantationsRes.erase(position);
        }
    }
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

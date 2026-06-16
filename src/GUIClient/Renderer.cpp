/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Renderer
*/

#include "Renderer.hpp"

Renderer::Renderer() {
    InitWindow(800, 600, "Zappy - Renderer");
    SetTargetFPS(60);

    _camera.target = Vector2{ 0.0f, 0.0f };
    _camera.offset = Vector2{ 400.0f, 300.0f };
    _camera.rotation = 0.0f;
    _camera.zoom = 1.0f;
}

Renderer::~Renderer() {
    CloseWindow();
}

bool Renderer::isWindowOpen() const {
    return !WindowShouldClose();
}

void Renderer::render(WorldState world) {
    (void)(world);
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(_camera);
    EndMode2D();

    EndDrawing();
}


void Renderer::loadTextures() {
}

void Renderer::renderMap(GUIMap map) {
    (void)map;
}

void Renderer::renderPlayers(std::map<PlayerId, GUIPlayer> players) {
    (void)players;
}

void Renderer::renderEggs(std::map<unsigned int, GUIEgg> eggs) {
    (void)eggs;
}

void Renderer::updateAnimation(GUIPlayer player) {
    (void)player;
}

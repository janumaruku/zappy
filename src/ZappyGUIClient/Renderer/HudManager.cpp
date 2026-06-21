/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HudManager
*/

#include "HudManager.hpp"

#include "Renderer.hpp"

namespace zappy::gui {

HUDManager::HUDManager()
{
    ARenderManager::loadTextures();
}

void HUDManager::loadImages()
{
    _images.insert({"backgroundTeam",
        GenImageColor(BACKGROUND_TEAM_WIDTH, BACKGROUND_TEAM_HEIGHT, WHITE)});
}
} // namespace zappy::gui

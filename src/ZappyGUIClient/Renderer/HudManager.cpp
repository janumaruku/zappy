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
    _images.insert({"bkgTeam",
        GenImageColor(BACKGROUND_TEAM_WIDTH, BACKGROUND_TEAM_HEIGHT, WHITE)});
    _images.insert({"bkgPlayerDropdown",
        GenImageColor(BACKGROUND_DROPDOWN_BUTTON_WIDTH, BACKGROUND_DROPDOWN_BUTTON_HEIGHT, WHITE)});
}
} // namespace zappy::gui

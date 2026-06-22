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
    _images.insert({BACKGROUND_TEAM_NAME,
        GenImageColor(BACKGROUND_TEAM_WIDTH, BACKGROUND_TEAM_HEIGHT, WHITE)});
    _images.insert({SELECT_DROPDOWN_BUTTON_NAME,
        GenImageColor(BACKGROUND_DROPDOWN_BUTTON_WIDTH,
            BACKGROUND_DROPDOWN_BUTTON_HEIGHT, WHITE)});
}
void HUDManager::loadRectangles()
{
    createRectangle(SELECT_DROPDOWN_BUTTON_NAME,
        {static_cast<float>(BACKGROUND_DROPDOWN_BUTTON_X),
            BACKGROUND_DROPDOWN_BUTTON_Y},
        BACKGROUND_DROPDOWN_BUTTON_WIDTH, BACKGROUND_DROPDOWN_BUTTON_HEIGHT);
}
} // namespace zappy::gui

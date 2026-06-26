/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HudManager
*/

#include "HudManager.hpp"

#include "Renderer.hpp"

namespace zappy::gui {

HUDManager::HUDManager(const WorldState &worldState)
{
    ARenderManager::loadTextures();
    loadPlayerDropdownRectangles(worldState);
}

void HUDManager::updateRectanglePlayers(const WorldState &worldState)
{
    int count = 0;

    for (const auto &[playerId, playerData] : worldState.getPlayers()) {
        if (!_rectangles.contains(playerId)) {
            data::Position playerRecPosition = {BACKGROUND_PLAYER_DROPDOWN_X,
        BACKGROUND_PLAYER_DROPDOWN_Y +
        (BACKGROUND_PLAYER_DROPDOWN_HEIGHT * count)};

            createRectangle(playerId,
                {static_cast<float>(playerRecPosition.getX()),
                    static_cast<float>(playerRecPosition.getY())},
                BACKGROUND_PLAYER_DROPDOWN_WIDTH,
                BACKGROUND_PLAYER_DROPDOWN_HEIGHT);
            ++count;
        }
    }
}

void HUDManager::loadPlayerDropdownRectangles(const WorldState &worldState)
{
    int count = 0;
    for (auto &it: worldState.getPlayers()) {
        data::Position playerRecPosition = {BACKGROUND_PLAYER_DROPDOWN_X,
            BACKGROUND_PLAYER_DROPDOWN_Y +
                (BACKGROUND_PLAYER_DROPDOWN_HEIGHT * count)};

        createRectangle(it.first,
            {static_cast<float>(playerRecPosition.getX()),
                static_cast<float>(playerRecPosition.getY())},
            BACKGROUND_PLAYER_DROPDOWN_WIDTH,
            BACKGROUND_PLAYER_DROPDOWN_HEIGHT);
        ++count;
    }
}


void HUDManager::loadImages()
{
    _images.insert({BACKGROUND_TEAM_NAME,
        GenImageColor(BACKGROUND_TEAM_WIDTH, BACKGROUND_TEAM_HEIGHT, WHITE)});
    _images.insert({SELECT_DROPDOWN_BUTTON_NAME,
        GenImageColor(BACKGROUND_DROPDOWN_BUTTON_WIDTH,
            BACKGROUND_DROPDOWN_BUTTON_HEIGHT, WHITE)});
    _images.insert({BACKGROUND_PLAYER_DROPDOWN_NAME,
    GenImageColor(BACKGROUND_PLAYER_DROPDOWN_WIDTH, BACKGROUND_PLAYER_DROPDOWN_HEIGHT, WHITE)});
    _images.insert({BACKGROUND_SELECTED_PLAYER_INFO_NAME,
    GenImageColor(BACKGROUND_SELECTED_PLAYER_INFO_WIDTH, BACKGROUND_SELECTED_PLAYER_INFO_HEIGHT, WHITE)});
}


void HUDManager::loadRectangles()
{
    createRectangle(SELECT_DROPDOWN_BUTTON_NAME,
        {static_cast<float>(BACKGROUND_DROPDOWN_BUTTON_X),
            BACKGROUND_DROPDOWN_BUTTON_Y},
        BACKGROUND_DROPDOWN_BUTTON_WIDTH, BACKGROUND_DROPDOWN_BUTTON_HEIGHT);

    createRectangle(BACKGROUND_SELECTED_PLAYER_INFO_NAME,
        {static_cast<float>(BACKGROUND_SELECTED_PLAYER_INFO_X), WINDOW_HEIGHT - BACKGROUND_SELECTED_PLAYER_INFO_WIDTH},
        BACKGROUND_SELECTED_PLAYER_INFO_WIDTH, BACKGROUND_SELECTED_PLAYER_INFO_HEIGHT);
}
} // namespace zappy::gui

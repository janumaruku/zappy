/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUDManager
*/

#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#include "ARenderManager.hpp"

namespace zappy::gui {

constexpr int BACKGROUND_TEAM_WIDTH  = 80;
constexpr int BACKGROUND_TEAM_HEIGHT = 30;

constexpr int BACKGROUND_DROPDOWN_BUTTON_X = BACKGROUND_TEAM_WIDTH;
constexpr int BACKGROUND_DROPDOWN_BUTTON_Y = 0;

constexpr int BACKGROUND_DROPDOWN_BUTTON_WIDTH  = 100;
constexpr int BACKGROUND_DROPDOWN_BUTTON_HEIGHT = 50;

constexpr int PLAYER_COUNT_Y_OFFSET = 10;

constexpr int TEXT_FONT_SIZE = 5;

const std::string SELECT_DROPDOWN_BUTTON_NAME = "PlayerSelectDropdownButton";

class HUDManager: public designPattern::ARenderManager {
public:
    HUDManager();
    ~HUDManager() override = default;

protected:
    void loadImages() override;
    void loadRectangles() override;
};
} // namespace zappy::gui

#endif // HUDMANAGER_HPP

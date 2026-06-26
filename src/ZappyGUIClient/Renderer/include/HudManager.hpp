/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUDManager
*/

#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#include "ARenderManager.hpp"
#include "WorldState.hpp"

namespace zappy::gui {
constexpr int BACKGROUND_TEAM_WIDTH  = 80;
constexpr int BACKGROUND_TEAM_HEIGHT = 30;

constexpr int BACKGROUND_DROPDOWN_BUTTON_X = BACKGROUND_TEAM_WIDTH;
constexpr int BACKGROUND_DROPDOWN_BUTTON_Y = 0;

constexpr int BACKGROUND_DROPDOWN_BUTTON_WIDTH  = 100;
constexpr int BACKGROUND_DROPDOWN_BUTTON_HEIGHT = 50;

constexpr int BACKGROUND_PLAYER_DROPDOWN_WIDTH =
    BACKGROUND_DROPDOWN_BUTTON_WIDTH;
constexpr int BACKGROUND_PLAYER_DROPDOWN_HEIGHT = 30;

constexpr int BACKGROUND_PLAYER_DROPDOWN_X = BACKGROUND_DROPDOWN_BUTTON_X;
constexpr int BACKGROUND_PLAYER_DROPDOWN_Y = BACKGROUND_DROPDOWN_BUTTON_HEIGHT;

constexpr int BACKGROUND_SELECTED_PLAYER_INFO_WIDTH  = 100;
constexpr int BACKGROUND_SELECTED_PLAYER_INFO_HEIGHT = 130;

constexpr int BACKGROUND_SELECTED_PLAYER_INFO_X = 0;

constexpr int PLAYER_COUNT_Y_OFFSET = 10;

constexpr int TEXT_FONT_SIZE = 5;

const std::string SELECT_DROPDOWN_BUTTON_NAME = "PlayerSelectDropdownButton";
const std::string BACKGROUND_PLAYER_DROPDOWN_NAME = "BackgroundPlayerDropdown";
const std::string BACKGROUND_SELECTED_PLAYER_INFO_NAME =
    "BackgroundSelectedPlayerInfo";
const std::string BACKGROUND_TEAM_NAME = "BackgroundTeam";

class HUDManager: public designPattern::ARenderManager {
public:
    HUDManager(const WorldState &worldState);
    ~HUDManager() override = default;

    void updateRectanglePlayers(const WorldState &worldState);
    void loadPlayerDropdownRectangles(const WorldState &worldState);

protected:
    void loadImages() override;
    void loadRectangles() override;
};
} // namespace zappy::gui

#endif // HUDMANAGER_HPP

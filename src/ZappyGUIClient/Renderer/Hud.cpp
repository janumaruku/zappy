/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUD
*/

#include "include/Hud.hpp"

#include <format>
#include <iostream>

#include "Renderer.hpp"

namespace zappy::gui {

void HUD::update(const std::unique_ptr<HUDManager> &hudManager)
{
    if (!_dropdownOpen) {
        onDropdownButton(hudManager);
    }
}
void HUD::draw(const WorldState &world,
    const std::unique_ptr<HUDManager> &hudManager) const
{
    size_t count = 0;

    for (const auto &it: world.getTeams()) {
        drawTeamsPanel(world.getPlayers(), it, static_cast<int>(count),
            hudManager);
        ++count;
    }
    drawTime(world.getTimeUnit());
    drawPlayerSelectorDropdownButton(hudManager);
}

bool HUD::isDropdownOpen() const
{
    return _dropdownOpen;
}

void HUD::onDropdownButton(const std::unique_ptr<HUDManager> &hudManager)
{
    const Vector2 &mousePosition = GetMousePosition();
    const Rectangle &dropdownButton =
        hudManager->getRectangle(SELECT_DROPDOWN_BUTTON_NAME);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(mousePosition, dropdownButton)) {
        _dropdownOpen = true;
        // drawPlayerSelectorDropdownButton(hudManager);
        std::cout << "dropdown button pressed" << std::endl;
    }
}

void HUD::drawTeamsPanel(const std::unordered_map<data::PlayerId, GUIPlayer>
                             &players,
    const std::pair<const std::string, Team> &team, const int &count,
    const std::unique_ptr<HUDManager> &hudManager)
{
    const auto teamPlayersNames = team.second.getPlayers();
    size_t maxPlayerCount = getMaxPlayersFromNames(players, teamPlayersNames);

    const std::string playerCountText =
        std::format("{} / {}", maxPlayerCount, teamPlayersNames.size());

    DrawTexture(hudManager->getTexture(BACKGROUND_TEAM_NAME), 0,
        BACKGROUND_TEAM_HEIGHT * count, team.second.getColor());
    DrawText(team.first.c_str(), 0, BACKGROUND_TEAM_HEIGHT * count,
        TEXT_FONT_SIZE, WHITE);
    DrawText(playerCountText.c_str(), 0,
        (BACKGROUND_TEAM_HEIGHT * count) + PLAYER_COUNT_Y_OFFSET,
        TEXT_FONT_SIZE, WHITE);
}

void HUD::drawTime(const int &timeUnit)
{
    const std::string timeText = std::format("Speed : {}", timeUnit);

    DrawText(timeText.c_str(),
        WINDOW_WIDTH - (TEXT_FONT_SIZE * timeText.size()), 0, TEXT_FONT_SIZE,
        WHITE);
}

void HUD::drawPlayerSelectorDropdownButton(const std::unique_ptr<HUDManager>
        &hudManager) const
{
    const data::Position textPos = {
        BACKGROUND_DROPDOWN_BUTTON_X + TEXT_FONT_SIZE,
        (BACKGROUND_DROPDOWN_BUTTON_HEIGHT - TEXT_FONT_SIZE) / 2};
    const Rectangle &selectDropdownButton =
        hudManager->getRectangle(SELECT_DROPDOWN_BUTTON_NAME);
    DrawTexture(hudManager->getTexture(SELECT_DROPDOWN_BUTTON_NAME),
        selectDropdownButton.x, selectDropdownButton.y, GRAY);

    if (!_selectedPlayerId.has_value()) {
        DrawText("Select Player", textPos.getX(), textPos.getY(),
            TEXT_FONT_SIZE, WHITE);
    } else {
        DrawText(_selectedPlayerId.value().c_str(), textPos.getX(),
            textPos.getY(), TEXT_FONT_SIZE, WHITE);
    }
}

void HUD::drawPlayerSelectorDropdown(const WorldState &worldState,
    const std::unique_ptr<HUDManager> &hudManager)
{
    size_t count = 0;
    for (auto &it: worldState.getPlayers()) {

        DrawTexture(hudManager->getTexture(BACKGROUND_TEAM_NAME),
            BACKGROUND_TEAM_WIDTH, BACKGROUND_DROPDOWN_BUTTON_HEIGHT * count,
            WHITE);
        DrawText(it.first.c_str(), BACKGROUND_TEAM_WIDTH,
            (BACKGROUND_DROPDOWN_BUTTON_HEIGHT * count) -
                (BACKGROUND_DROPDOWN_BUTTON_HEIGHT / 2),
            TEXT_FONT_SIZE, BLACK);
        ++count;
    }
}

size_t HUD::getMaxPlayersFromNames(const std::unordered_map<data::PlayerId,
                                       GUIPlayer> &players,
    const std::vector<data::PlayerId> &playerNames)
{
    size_t count = 0;
    for (const auto &name: playerNames)
        if (players.at(name).getLevel() == 8)
            ++count;
    return count;
}
} // namespace zappy::gui

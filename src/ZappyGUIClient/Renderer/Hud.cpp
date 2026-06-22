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

void HUD::draw(const WorldState &world,
    const std::unique_ptr<HUDManager> &hudManager) const
{
    size_t count = 0;

    for (const auto &it: world.getTeams()) {
        drawTeamsPanel(
            world.getPlayers(), it, static_cast<int>(count),hudManager);
        ++count;
    }
    drawTime(world.getTimeUnit());
    drawPlayerSelectorDropdownButton(hudManager);
}

void HUD::drawTeamsPanel(
    const std::unordered_map<data::PlayerId, GUIPlayer> &players,
    const std::pair<const std::string, Team> &team, const int &count,
    const std::unique_ptr<HUDManager> &hudManager)
{
    const auto teamPlayersNames = team.second.getPlayers();
    size_t maxPlayerCount = getMaxPlayersFromNames(players, teamPlayersNames);

    const std::string playerCountText =
        std::format("{} / {}", maxPlayerCount, teamPlayersNames.size());

    DrawTexture(hudManager->getTexture("bkgTeam"), 0,
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
    const data::Position position = {BACKGROUND_TEAM_WIDTH + TEXT_FONT_SIZE,
        (BACKGROUND_DROPDOWN_BUTTON_HEIGHT - TEXT_FONT_SIZE) / 2};

    DrawTexture(hudManager->getTexture("bkgPlayerDropdown"),
        BACKGROUND_TEAM_WIDTH, 0, GRAY);

    if (!_selectedPlayerId.has_value()) {
        DrawText("Select Player", position.getX(), position.getY(),
            TEXT_FONT_SIZE, WHITE);
    } else {
        DrawText(_selectedPlayerId.value().c_str(), position.getX(),
            position.getY(), TEXT_FONT_SIZE, WHITE);
    }
}

void HUD::drawPlayerSelectorDropdown(const WorldState &worldState,
    const std::unique_ptr<HUDManager> &hudManager)
{
    size_t count = 0;
    for (auto &it: worldState.getPlayers()) {
        DrawTexture(hudManager->getTexture("bkgPlayerDropdown"),
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

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

void HUD::update(const WorldState &world,
    const std::unique_ptr<HUDManager> &hudManager)
{
    if (!_dropdownOpen) {
        onDropdownButton(hudManager);
    } else {
        onDropdownPlayerSelected(hudManager, world.getPlayers());
    }
}

void HUD::draw(const WorldState &worldState,
    const std::unique_ptr<HUDManager> &hudManager) const
{
    size_t count = 0;

    for (const auto &it: worldState.getTeams()) {
        drawTeamsPanel(worldState.getPlayers(), it, static_cast<int>(count),
            hudManager);
        ++count;
    }

    drawTime(worldState.getTimeUnit());
    drawPlayerSelectorDropdownButton(hudManager);
    if (_dropdownOpen) {
        drawPlayerSelectorDropdown(worldState, hudManager);
    }
    if (_selectedPlayerId.has_value()) {
        drawSelectedPlayer(worldState.getPlayerById(_selectedPlayerId.value()),
            hudManager);
    }
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
    }
}
void HUD::onDropdownPlayerSelected(const std::unique_ptr<HUDManager>
                                       &hudManager,
    const std::unordered_map<data::PlayerId, GUIPlayer> &players)
{
    const Vector2 &mousePosition = GetMousePosition();

    for (const auto &it: players) {
        const Rectangle rectangle = hudManager->getRectangle(it.first);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            CheckCollisionPointRec(mousePosition, rectangle)) {
            _selectedPlayerId = it.first;
            _dropdownOpen     = false;
        }
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
    for (auto &it: worldState.getPlayers()) {

        const Rectangle &playerRectangle = hudManager->getRectangle(it.first);
        const Team &playerTeam = worldState.getTeams().at(it.second.getTeam());

        DrawTextureRec(hudManager->getTexture(BACKGROUND_PLAYER_DROPDOWN_NAME),
            playerRectangle, {playerRectangle.x, playerRectangle.y},
            worldState.getTeams().at(it.second.getTeam()).getColor());

        DrawTexture(hudManager->getTexture(BACKGROUND_PLAYER_DROPDOWN_NAME),
            playerRectangle.x, playerRectangle.y, playerTeam.getColor());

        DrawText(it.first.c_str(), playerRectangle.x,
            playerRectangle.y, TEXT_FONT_SIZE, BLACK);
    }
}

void HUD::drawSelectedPlayer(const GUIPlayer &player,
    const std::unique_ptr<HUDManager> &hudManager)
{
    data::Position position = {BACKGROUND_SELECTED_PLAYER_INFO_X,
        static_cast<int>(WINDOW_HEIGHT - BACKGROUND_SELECTED_PLAYER_INFO_HEIGHT)};

    DrawTexture(hudManager->getTexture(BACKGROUND_SELECTED_PLAYER_INFO_NAME),
        position.getX(), position.getY(), GRAY);

    DrawText(std::format("player : {}", player.getId()).c_str(),
        position.getX(), position.getY(), TEXT_FONT_SIZE, WHITE);

    DrawText(std::format("team : {}", player.getTeam()).c_str(),
        position.getX(), position.getY() + (TEXT_FONT_SIZE * 2), TEXT_FONT_SIZE,
        WHITE);

    DrawText(std::format("level : {}", player.getLevel()).c_str(),
        position.getX(), position.getY() + (TEXT_FONT_SIZE * 4), TEXT_FONT_SIZE,
        WHITE);

    size_t offsetY = 6;
    for (const auto &it: player.getInventory()) {
        DrawText(std::format("{} : {}",
            RESOURCE_DATA[static_cast<int>(it.first)].name, it.second).c_str(),
            position.getX(), position.getY() + (TEXT_FONT_SIZE * offsetY),
            TEXT_FONT_SIZE, WHITE);

        offsetY += 2;
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

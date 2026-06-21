/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUD
*/

#include "include/Hud.hpp"

#include <format>
#include <iostream>

namespace zappy::gui {

void HUD::draw(const WorldState &world,
    const std::unique_ptr<HUDManager> &hudManager)
{
    size_t count = 0;

    for (const auto &it: world.getTeams()) {
        drawTeamsPanel(world.getPlayers(), it, static_cast<int>(count), hudManager);
        ++count;
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

    DrawTexture(hudManager->getTexture("backgroundTeam"), 0,
        BACKGROUND_TEAM_HEIGHT * count, team.second.getColor());
    DrawText(team.first.c_str(), 0, BACKGROUND_TEAM_HEIGHT * count, 5, WHITE);
    DrawText(playerCountText.c_str(), 0, (BACKGROUND_TEAM_HEIGHT * count) + 10,
        5, WHITE);
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

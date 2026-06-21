/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUD
*/

#include "include/Hud.hpp"

#include <format>

namespace zappy::gui {

void HUD::draw(const WorldState &world)
{
    const auto& teams = world.getTeams();
    const auto& players = world.getPlayers();

    size_t count = 0;
    for (const auto &it : teams) {
        drawTeamsPanel(players, it, count);
    }

}

void HUD::drawTeamsPanel(
    const std::unordered_map<data::PlayerId, GUIPlayer>&players,
    const std::pair<const std::string, Team> &team, size_t count)
{
    const auto teamPlayersNames = team.second.getPlayers();

    const Image teamBackImage = GenImageColor(100, 50, team.second.getColor());

    size_t maxPlayerCount = 0;
    for (const auto &name : teamPlayersNames) {
        if (players.at(name).getLevel() == 8) {
            ++maxPlayerCount;
        }
    }
    DrawTexture(LoadTextureFromImage(teamBackImage), 1 * count, 1 * count, WHITE);
    DrawText(team.first.c_str(), 1 * count + 10, 1 * count + 10, 5, WHITE);

    const std::string playerCountText = std::format("{} / {}",maxPlayerCount, teamPlayersNames.size());
    DrawText(playerCountText.c_str(), 1 + count + 10, 1 * count + 20, 5, WHITE);
    ++count;
}
} // gui
// zappy
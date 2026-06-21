/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUD
*/

#ifndef HUD_HPP
#define HUD_HPP
#include <memory>
#include <optional>

#include "Egg.hpp"
#include "HudManager.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

class HUD {
public:
    HUD() = default;
    static void draw(const WorldState &world,
        const std::unique_ptr<HUDManager> &hudManager);

private:
    std::optional<data::PlayerId> _selectedPlayerId;
    bool _dropdownOpen = false;

    static void drawTeamsPanel(const std::unordered_map<data::PlayerId,
                                   GUIPlayer> &players,
        const std::pair<const std::string, Team> &team, const size_t &count,
        const std::unique_ptr<HUDManager> &hudManager);

    static size_t getMaxPlayersFromNames(
        const std::unordered_map<data::PlayerId,GUIPlayer> &players,
        const std::vector<data::PlayerId> &PlayerNames);
};
} // namespace zappy::gui

#endif // HUD_HPP

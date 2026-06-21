/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUD
*/

#ifndef HUD_HPP
#define HUD_HPP
#include <optional>

#include "Egg.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

class HUD {
public:
    HUD() = default;
    static void draw(const WorldState &world);

private:
    std::optional<data::PlayerId> _selectedPlayerId;
    bool _dropdownOpen = false;

    static void drawTeamsPanel(
        const std::unordered_map<data::PlayerId,GUIPlayer> &players,
        const std::pair<const std::string, Team> &team, size_t count);


};
} // namespace zappy::gui

#endif // HUD_HPP

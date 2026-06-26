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

constexpr int MAX_LEVEL = 8;

class HUD {
public:
    HUD() = default;
    void update(const WorldState &world, const std::unique_ptr<HUDManager> &hudManager);

    void draw(const WorldState &worldState,
        const std::unique_ptr<HUDManager> &hudManager) const;

    bool isDropdownOpen() const;

    void onDropdownButton(const std::unique_ptr<HUDManager> &hudManager);

    void onDropdownPlayerSelected(const std::unique_ptr<HUDManager> &hudManager,
        const std::unordered_map<data::PlayerId, GUIPlayer> &players);

private:
    std::optional<data::PlayerId> _selectedPlayerId;
    bool _dropdownOpen = false;

    static void drawTeamsPanel(const std::unordered_map<data::PlayerId,
                                   GUIPlayer> &players,
        const std::pair<const std::string, Team> &team, const int &count,
        const std::unique_ptr<HUDManager> &hudManager);

    static void drawTime(const int &timeUnit);

    void drawPlayerSelectorDropdownButton(const std::unique_ptr<HUDManager>
            &hudManager) const;

    static void drawPlayerSelectorDropdown(const WorldState &worldState,
        const std::unique_ptr<HUDManager> &hudManager);

    static void drawSelectedPlayer(const GUIPlayer &player,
        const std::unique_ptr<HUDManager> &hudManager);

    static size_t getMaxPlayersFromNames(
        const std::unordered_map<data::PlayerId, GUIPlayer> &players,
        const std::vector<data::PlayerId> &playerNames);
};
} // namespace zappy::gui

#endif // HUD_HPP

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
    void draw(const WorldState &world);

private:
    std::optional<data::PlayerId> _selectedPlayerId;
    bool _dropdownOpen = false;
};
} // namespace zappy::gui

#endif // HUD_HPP

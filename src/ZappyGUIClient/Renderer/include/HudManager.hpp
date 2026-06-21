/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** HUDManager
*/

#ifndef HUDMANAGER_HPP
#define HUDMANAGER_HPP

#include "ARenderManager.hpp"

namespace zappy::gui {

constexpr int BACKGROUND_TEAM_WIDTH  = 80;
constexpr int BACKGROUND_TEAM_HEIGHT = 30;

class HUDManager: public designPattern::ARenderManager {
public:
    HUDManager();
    ~HUDManager() override = default;

protected:
    void loadImages() override;
};
} // namespace zappy::gui

#endif // HUDMANAGER_HPP

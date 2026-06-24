/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ZappyEvents
*/

#include "ZappyEvents.hpp"
#include "GUIPlayer.hpp"

namespace zappy::gui {
PlayerNewEvent::PlayerNewEvent(const GUIPlayer &player): id{player.getId()},
    position{player.getPosition()}, orientation{player.getOrientation()},
    level{player.getLevel()}, team{player.getTeam()}
{
}

PlayerMovedEvent::PlayerMovedEvent(const GUIPlayer &player): id{player.getId()},
    position{player.getPosition()}, orientation{player.getOrientation()}
{
}

PlayerLevelEvent::PlayerLevelEvent(const GUIPlayer &player) : id(player.getId()),
level(player.getLevel()), team(player.getTeam())
{}
}

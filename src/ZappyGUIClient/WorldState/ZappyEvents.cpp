/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ZappyEvents
*/

#include "ZappyEvents.hpp"

namespace zappy::gui {
PlayerNewEvent::PlayerNewEvent(const GUIPlayer &player): id{player.getId()},
    position{player.getPosition()}, orientation{player.getOrientation()},
    level{player.getLevel()}, team{player.getTeam()}
{
}

PlayerMovedEvent::PlayerMovedEvent(GUIPlayer &player): id{player.getId()},
    position{player.getPosition()}, orientation{player.getOrientation()}
{
    if (!player.hasAction())
        return;
    action = player.dequeueAction();
}
}

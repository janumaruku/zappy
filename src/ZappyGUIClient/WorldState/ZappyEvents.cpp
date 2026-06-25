/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ZappyEvents
*/

#include "ZappyEvents.hpp"

#include <utility>
#include "GUIPlayer.hpp"
#include "Position.hpp"

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

PlayerInventoryAssignEvent::PlayerInventoryAssignEvent(GUIPlayer &player) :
id(player.getId()), inventory(player.getInventory())
{}

TimeUpdateEvent::TimeUpdateEvent(uint t) : timeUint(t) {}

PlayerBroadcastEvent::PlayerBroadcastEvent(const GUIPlayer &player, std::string msg) :
id(player.getId()), msg(std::move(msg)) {}

TileUpdateEvent::TileUpdateEvent(const data::Position &pos, const std::unordered_map<data::Resource, int> &resources) :
position(pos), resources(resources) {}

IncantationStartEvent::IncantationStartEvent(data::Position pos,
        uint level, data::PlayerId id,
        std::vector<data::PlayerId> participants) :
        position(pos), level(level), initiatorId(std::move(id)), participants(std::move(participants)) {}
 
}

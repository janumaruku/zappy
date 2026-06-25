/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ZappyEvents
*/

#ifndef ZAPPY_ZAPPYEVENTS_HPP
#define ZAPPY_ZAPPYEVENTS_HPP

#include <unordered_map>
#include <variant>
#include <vector>

#include "Egg.hpp"
#include "GUIPlayer.hpp"
#include "Position.hpp"
#include "Tile.hpp"

namespace zappy::gui {
struct PlayerNewEvent {
    explicit PlayerNewEvent(const GUIPlayer &player);

    data::PlayerId id;
    data::Position position;
    data::Orientation orientation;
    uint8_t level;
    std::string team;
};

struct PlayerLevelEvent {
    explicit PlayerLevelEvent(const GUIPlayer &player);
    data::PlayerId id;
    uint8_t level;
    std::string team;
};

struct PlayerInventoryAssignEvent {
    explicit PlayerInventoryAssignEvent(GUIPlayer &player);
    data::PlayerId id;
    const std::unordered_map<data::Resource, uint> &inventory;
};

struct PlayerMovedEvent {
    explicit PlayerMovedEvent(GUIPlayer &player);

    Action action{};
    data::PlayerId id;
    data::Position position;
    data::Orientation orientation;
};

struct PlayerDiedEvent {
    data::PlayerId id;
};

struct PlayerBroadcastEvent {
    explicit PlayerBroadcastEvent(const GUIPlayer &player, std::string msg);
    data::PlayerId id;
    std::string msg;
};

struct TileUpdateEvent {
    explicit TileUpdateEvent(const data::Position &pos, const std::unordered_map<data::Resource, int> &resources);
    data::Position position;
    const std::unordered_map<data::Resource, int> &resources;
};

struct TimeUpdateEvent {
    explicit TimeUpdateEvent(uint timeUnit);
    uint timeUint;
};

struct EggLaidEvent {
    std::string eggId;
    data::PlayerId playerId;
    data::Position position;
};

struct EggHatchedEvent {
    std::string egdId;
};

struct EggDiedEvent {
    std::string egdId;
};

struct IncantationStartEvent {
    explicit IncantationStartEvent(data::Position pos,
        uint level, data::PlayerId id,
        std::vector<data::PlayerId> participants);
        
    data::Position position;
    uint8_t level;
    data::PlayerId initiatorId;
    std::vector<data::PlayerId> participants;
};

struct IncantationEndEvent {
    data::Position position;
    bool result = false;
};

struct GameEndEvent {
    std::string team;
};

using ZappyEvent = std::variant<PlayerNewEvent, PlayerMovedEvent, PlayerLevelEvent,
    PlayerInventoryAssignEvent, PlayerDiedEvent, PlayerBroadcastEvent,
    TileUpdateEvent,
    TimeUpdateEvent,
    EggLaidEvent, EggHatchedEvent, EggDiedEvent,
    IncantationStartEvent, IncantationEndEvent, GameEndEvent>;
}

#endif //ZAPPY_ZAPPYEVENTS_HPP

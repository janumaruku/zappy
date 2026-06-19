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

struct PlayerMovedEvent {
    explicit PlayerMovedEvent(const GUIPlayer &player);

    data::PlayerId id;
    data::Position position;
    data::Orientation orientation;
};

struct PlayerDiedEvent {
    data::PlayerId id;
};

struct TileUpdateEvent {
    data::Position position;
    std::unordered_map<data::Resource, uint> resources;
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
    data::Position position;
    uint8_t level;
    std::vector<data::PlayerId> playerIds;
};

struct IncantationEndEvent {
    data::Position position;
    bool result = false;
};

struct GameEndEvent {
    std::string team;
};

using ZappyEvent = std::variant<PlayerNewEvent, PlayerMovedEvent,
    PlayerDiedEvent, TileUpdateEvent, EggLaidEvent, EggHatchedEvent,
    EggDiedEvent, IncantationStartEvent, IncantationEndEvent>;
}

#endif //ZAPPY_ZAPPYEVENTS_HPP

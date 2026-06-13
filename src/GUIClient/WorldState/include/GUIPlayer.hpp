/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.hpp
*/

#ifndef GUIPLAYER_HPP
#define GUIPLAYER_HPP
#include <cstdint>
#include <unordered_map>
#include <queue>
#include <string>

#include "Position.hpp"
#include "Tile.hpp"

namespace zappy::gui {
enum class Orientation : std::uint8_t {
    NORTH,
    WEST,
    SOUTH,
    EAST,
};

enum class ActionType : std::uint8_t {
    FORWARD,
    LEFT,
    RIGHT,
    LOOK,
    INVENTORY,
    BROADCAST,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION,
    DEATH,
};

struct Action {
    ActionType type;
    float duration;
};

class GUIPlayer {
    using PlayerId = std::string;

public:

    // Prefer this constructor over the second one since the orietation is randomized
    //  when the player is created
    explicit GUIPlayer(const PlayerId &id, const std::string &team,
        const data::Position &position, uint8_t level);

    explicit GUIPlayer(const PlayerId &id, const std::string &team,
        const data::Position &position,
        const Orientation &orientation, uint8_t level);

    [[nodiscard]] const PlayerId &getId() const;
    [[nodiscard]] const std::string &getTeam() const;
    [[nodiscard]] const data::Position &getPosition() const;
    [[nodiscard]] const Orientation &getOrientation() const;
    [[nodiscard]] const uint8_t &getLevel() const;

    void enqueueAction(Action action);

    Action dequeueAction();

    [[nodiscard]] bool hasAction() const;

    
private:
    static Orientation randomizedOrientation();

    PlayerId _id;
    std::string _team;
    data::Position _position;
    Orientation _orientation;
    uint8_t _level = 0;
    std::unordered_map<data::Resource, uint> _inventory;
    std::queue<Action> _actionQueue;
};

}

#endif

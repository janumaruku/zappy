/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.hpp
*/

#ifndef GUIPLAYER_HPP
#define GUIPLAYER_HPP
#include <cstdint>
#include <map>
#include <queue>
#include <string>

#include "Position.hpp"
#include "Tile.hpp"

namespace zappy::gui {
enum class Orientation : std::uint8_t {
    NORTH = 0,
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
    GUIPlayer(const PlayerId &id, const std::string &team,
        const data::Position &position, uint8_t level);

    [[nodiscard]] PlayerId getId() const;

    [[nodiscard]] std::string getTeam() const;

    [[nodiscard]] data::Position getPosition() const;

    [[nodiscard]] Orientation getOrientation() const;

    uint8_t &getLevel();

    void enqueueAction(Action action);

    Action dequeueAction();

    [[nodiscard]] bool hasAction() const;

private:
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

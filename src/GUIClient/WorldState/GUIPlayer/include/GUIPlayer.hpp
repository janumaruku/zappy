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
    GUIPlayer(const PlayerId &id, const std::string &team,
        const data::Position &position,
        const Orientation &orientation, uint8_t level);

    PlayerId getId() const;

    std::string getTeam() const;

    data::Position getTilePosition() const;

    Orientation &getOrientation();

    uint8_t &getLevel();

    void enqueueAction(Action action);

    Action dequeueAction();

    bool hasAction() const;

private:
    PlayerId _id;
    std::string _team;
    data::Position _position;
    Orientation _orientation = Orientation::NORTH;
    uint8_t _level = 0;
    std::map<data::Resource, uint> _inventory;
    std::queue<Action> _actionQueue;
};

}

#endif

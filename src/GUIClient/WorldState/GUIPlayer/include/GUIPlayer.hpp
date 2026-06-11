/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.hpp
*/

#ifndef GUIPLAYER_HPP
#define GUIPLAYER_HPP
#include <cstdint>
#include <queue>
#include <string>

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

class GUIPlayer {
    using PlayerId = std::string;

    struct Action {
        ActionType type;
        float duration;
    };

public:
    GUIPlayer(PlayerId id, std::string team, /*Position position,*/
        Orientation orientation, uint8_t level);

    PlayerId getId() const;

    std::string getTeam() const;

    //Position getTilePosition();

    Orientation getOrientation() const;

    uint8_t getLevel() const;

    void enqueueAction(Action action);

    Action dequeueAction();

    bool hasAction() const;

private:
    PlayerId _id;
    std::string _team;
    //Position _position;
    Orientation _orientation = Orientation::NORTH;
    uint8_t _level = 0;
    //map<Ressource, uint> _inventory;
    std::queue<Action> _actionQueue;
};

}

#endif

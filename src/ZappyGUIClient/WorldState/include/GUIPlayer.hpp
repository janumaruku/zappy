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

#include "Position.hpp"
#include "Tile.hpp"

namespace zappy::gui {
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
        const data::Position &position, data::Orientation orientation,
        uint8_t level);

    [[nodiscard]] PlayerId getId() const;

    [[nodiscard]] std::string getTeam() const;

    [[nodiscard]] data::Position getPosition() const;
    void setPosition(const data::Position &);

    [[nodiscard]] data::Orientation getOrientation() const;
    void setOrientation(const data::Orientation &);

    uint8_t getLevel() const;
    void setLevel(uint8_t lvl) noexcept;

    const std::unordered_map<data::Resource, uint> &getInventory() const;

    void enqueueAction(Action action);

    Action dequeueAction();

    [[nodiscard]] bool hasAction() const;

private:
    PlayerId _id;
    std::string _team;
    data::Position _position;
    data::Orientation _orientation;
    uint8_t _level = 0;
    std::unordered_map<data::Resource, uint> _inventory;
    std::queue<Action> _actionQueue;
};

}

#endif

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIEgg.hpp
*/

#ifndef GUIEGG_HPP
#define GUIEGG_HPP
#include <string>

#include "Position.hpp"

namespace zappy::data {
using PlayerId = std::string;

class Egg {
public:
    Egg(const std::string &id, const PlayerId &playerId,
        const std::string &team, const Position &position, uint level);

    [[nodiscard]] std::string getId() const;

    PlayerId getPlayerId();
    [[nodiscard]] const PlayerId getPlayerId() const;

    [[nodiscard]] Position getPosition() const;

    std::string getTeam();
    [[nodiscard]] const std::string getTeam() const;

    [[nodiscard]] uint getLevel() const;

private:
    std::string _id;
    PlayerId _playerId;
    std::string _team;
    Position _position;
    uint _level;

};
}

#endif

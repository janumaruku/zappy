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
using TeamId = std::string;

class Egg {
public:
    Egg(std::string id, PlayerId playerId,
        std::string team, Position position, uint level);

    [[nodiscard]] std::string getId() const;

    [[nodiscard]] const PlayerId &getPlayerId() const;

    [[nodiscard]] Position getPosition() const;

    [[nodiscard]] TeamId &getTeam();
    [[nodiscard]] const TeamId &getTeam() const;

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

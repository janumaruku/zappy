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

namespace zappy::gui {
using PlayerId = std::string;

class GUIEgg {
public:
    GUIEgg(uint id, const PlayerId &playerId, const std::string &team, data::Position position);

    uint getId() const;

    PlayerId getPlayerId();

    data::Position getPosition() const;

    std::string getTeam();

    uint &getLevel();

private:
    uint _id;
    PlayerId _playerId;
    std::string _team;
    data::Position _position;
    uint _level = 1;

};
}

#endif

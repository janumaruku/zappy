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
    GUIEgg(uint id, const PlayerId &playerId, data::Position position);

    uint getId() const;

    PlayerId getPlayerId();

    data::Position getPosition() const;

private:
    uint _id;
    PlayerId _playerId;
    data::Position _position;

};
}

#endif

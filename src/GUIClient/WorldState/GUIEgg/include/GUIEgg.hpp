/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIEgg.hpp
*/

#ifndef GUIEGG_HPP
#define GUIEGG_HPP
#include <string>

namespace zappy::gui {
using PlayerId = std::string;

class GUIEgg {
public:
    GUIEgg(uint id, PlayerId playerId /*, Position position */);

    uint getId();

    PlayerId getPlayerId();

    //Position getPosition();
private:
    uint _id;
    PlayerId _playerId;
    //Position _position;

};
}

#endif

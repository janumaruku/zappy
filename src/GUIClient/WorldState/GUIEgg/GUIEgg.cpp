/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIEgg.cpp
*/

#include "GUIEgg.hpp"

namespace zappy::gui {
GUIEgg::GUIEgg(uint id, PlayerId playerId /*, Position position*/): _id(id),
    _playerId(playerId) /*_position(position)*/
{

}

uint GUIEgg::getId()
{
    return _id;
}

PlayerId GUIEgg::getPlayerId()
{
    return _playerId;
}

/*Position GUIEgg::getPosition()
{
    return _position;
}
 */
}

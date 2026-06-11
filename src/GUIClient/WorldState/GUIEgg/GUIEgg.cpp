/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIEgg.cpp
*/

#include "GUIEgg.hpp"

namespace zappy::gui {
GUIEgg::GUIEgg(const uint id, const PlayerId &playerId,
    const data::Position position): _id(id),
    _playerId(playerId), _position(position)
{

}

uint GUIEgg::getId() const
{
    return _id;
}

PlayerId GUIEgg::getPlayerId()
{
    return _playerId;
}

data::Position GUIEgg::getPosition() const
{
    return _position;
}

}

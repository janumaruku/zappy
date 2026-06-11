/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.cpp
*/

#include "GUIPlayer.hpp"

#include <iostream>

namespace zappy::gui {
GUIPlayer::GUIPlayer(PlayerId id, std::string team, /*Position position,*/
    Orientation orientation, uint8_t level): _id(id), _team(team),
    _orientation(orientation), _level(level)
{

}

GUIPlayer::PlayerId GUIPlayer::getId() const
{
    return _id;
}

std::string GUIPlayer::getTeam() const
{
    return _team;
}

/*Position GUIPlayer::getTilePosition(){
    return _position;
}
*/

Orientation GUIPlayer::getOrientation() const
{
    return _orientation;
}

uint8_t GUIPlayer::getLevel() const
{
    return _level;
}

void GUIPlayer::enqueueAction(Action action)
{
    _actionQueue.push(action);
}

GUIPlayer::Action GUIPlayer::dequeueAction()
{
    if (_actionQueue.empty()) {
        std::clog << "No action to dequeue" << std::endl;
        //error
    }
    const Action action = _actionQueue.front();
    _actionQueue.pop();
    return action;
}

bool GUIPlayer::hasAction() const
{
    if (_actionQueue.empty()) {
        return false;
    }
    return true;
}
}

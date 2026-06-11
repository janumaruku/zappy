/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.cpp
*/

#include "GUIPlayer.hpp"

#include <iostream>

namespace zappy::gui {
GUIPlayer::GUIPlayer(const PlayerId &id, const std::string &team,
    const data::Position position,
    const Orientation orientation, const uint8_t level): _id(id), _team(team),
    _position(position), _orientation(orientation), _level(level)
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

data::Position GUIPlayer::getTilePosition() const
{
    return _position;
}

Orientation GUIPlayer::getOrientation() const
{
    return _orientation;
}

uint8_t GUIPlayer::getLevel() const
{
    return _level;
}

void GUIPlayer::enqueueAction(const Action action)
{
    _actionQueue.push(action);
    std::clog << "added action to queue" << std::endl;
}

Action GUIPlayer::dequeueAction()
{
    if (_actionQueue.empty()) {
        throw std::runtime_error("No action to dequeue");
    }
    const Action action = _actionQueue.front();
    _actionQueue.pop();
    std::clog << "removed action from queue" << std::endl;
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

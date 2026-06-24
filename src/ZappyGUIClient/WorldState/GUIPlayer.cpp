/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.cpp
*/


#include <iostream>

#include "Position.hpp"
#include "GUIPlayer.hpp"
#include "constants.hpp"

namespace zappy::gui {

GUIPlayer::GUIPlayer(const PlayerId &id, const std::string &team,
    const data::Position &position, data::Orientation orientation,
    const uint8_t level): _id(id), _team(team),
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

data::Position GUIPlayer::getPosition() const
{
    return _position;
}

void GUIPlayer::setPosition(const data::Position &to)
{
    _position = to;
}

data::Orientation GUIPlayer::getOrientation() const
{
    return _orientation;

}

void GUIPlayer::setOrientation(const data::Orientation &to)
{
    _orientation = to;
}

uint8_t GUIPlayer::getLevel() const
{
    return _level;
}

const std::unordered_map<data::Resource, uint> &GUIPlayer::getInventory() const
{
    return _inventory;
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
    return _actionQueue.empty();
}
}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** GUIPlayer.cpp
*/

#include "GUIPlayer.hpp"
#include <random>
#include <iostream>

namespace zappy::gui {


GUIPlayer::GUIPlayer(const PlayerId &id, const std::string &team,
    const data::Position &position, const uint8_t level): _id(id), _team(team),
    _position(position), _orientation(randomizedOrientation()), _level(level) {}

GUIPlayer::GUIPlayer(const PlayerId &id, const std::string &team,
    const data::Position &position,
    const Orientation &orientation, const uint8_t level): _id(id), _team(team),
    _position(position), _orientation(orientation), _level(level) {}

Orientation GUIPlayer::randomizedOrientation()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    return static_cast<Orientation>(dis(gen));
}

const GUIPlayer::PlayerId &GUIPlayer::getId() const
{
    return _id;
}

const std::string &GUIPlayer::getTeam() const
{
    return _team;
}

const data::Position &GUIPlayer::getPosition() const
{
    return _position;
}

const Orientation &GUIPlayer::getOrientation() const
{
    return _orientation;
}

const uint8_t &GUIPlayer::getLevel() const
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
    return _actionQueue.empty();
}
}

/*
** EPITECH PROJECT, 2025
** ZPY
** File description
** Player.cpp
*/

#include "Player.hpp"
#include <algorithm>

namespace zappy::server {

Player::Player(const PlayerId &id, const TeamId &team, const zappy::data::Position &position, const std::uint8_t &level)
: _id(id), _team(team), _position(position), _level(level) {}

void Player::left()
{
    switch (_orientation) {
        case UP:
            _orientation = LEFT;
            break;
            case DOWN:
                _orientation = RIGHT;
        case LEFT:
            _orientation = DOWN;
            break;
            break;
        case RIGHT:
            _orientation = UP;
            break;
    }
}

void Player::forward()
{
    switch (_orientation) {
        case UP:
            _position.y--;
            break;
        case DOWN:
            _position.y++;
            break;
        case LEFT:
            _position.x--;
            break;
        case RIGHT:
            _position.x++;
            break;
    }
}

void Player::right()
{
    switch (_orientation) {
        case UP:
            _orientation = RIGHT;
            break;
        case DOWN:
            _orientation = LEFT;
            break;
        case LEFT:
            _orientation = DOWN;
            break;
        case RIGHT:
            _orientation = UP;
            break;
    }
}

bool Player::eatFood()
{
    return _inventory.erase(Resource::FOOD) > 0;
}

bool Player::takeResource(const Resource& resource)
{
    _inventory[resource]++;
    return true;
}

}
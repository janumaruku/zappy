/*
** EPITECH PROJECT, 2025
** ZPY
** File description
** Player.cpp
*/

#include "Player.hpp"
#include "constants.hpp"

namespace zappy::server {
Player::Player(const PlayerId &id, const TeamId &team,
    const data::Position &position, const std::uint8_t &level): _id{id},
    _team{team}, _position{position}, _level{level}
{
    _orientation = static_cast<data::Orientation>(utils::randomNumber(0, 3));
    _inventory[data::Resource::FOOD] = 10;

    for (auto i = 1; i < 7; ++i)
        _inventory[static_cast<data::Resource>(i)] = 0;
}

void Player::left()
{
    _orientation = static_cast<data::Orientation>((static_cast<int>(
            _orientation)
        + 1) % 4);
}

void Player::forward(const int width, const int height)
{
    auto &pos = _position;
    switch (_orientation) {
    case data::Orientation::UP:
        pos = (pos - data::Position{0, 1}) % data::Position{1, width};
        break;
    case data::Orientation::DOWN:
        pos = (pos + data::Position{0, 1}) % data::Position{1, height};
        break;
    case data::Orientation::LEFT:
        pos = (pos - data::Position{1, 0}) % data::Position{width, 1};
        break;
    case data::Orientation::RIGHT:
        pos = (pos + data::Position{1, 0}) % data::Position{width, 1};
        break;
    }
}

void Player::right()
{
    if (static_cast<int>(_orientation) == 0) {
        _orientation = data::Orientation::LEFT;
        return;
    }

    _orientation = static_cast<data::Orientation>(static_cast<int>(_orientation)
        - 1);
}

void Player::takeResource(const data::Resource &resource)
{
    _inventory[resource]++;
}

PlayerId Player::getId() const noexcept
{
    return _id;
}

TeamId Player::getTeam() const noexcept
{
    return _team;
}
data::Position Player::getPosition() const noexcept
{
    return _position;
}
std::uint8_t Player::getLevel() const noexcept
{
    return _level;
}

data::Orientation Player::getOrientation() const noexcept
{
    return _orientation;
}
}

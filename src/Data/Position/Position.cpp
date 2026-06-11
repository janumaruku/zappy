/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Position.cpp
*/

#include "Position.hpp"

#include <stdexcept>

namespace zappy::data {
Position::Position(int x, int y): _x(x), _y(y)
{

}

int Position::getX() const
{
    return _x;
}

int Position::getY() const
{
    return _y;
}

Position Position::operator+(Position other) const
{
    return {_x + other._x, _y + other._y};
}

void Position::operator+=(Position other)
{
    _x += other._x;
    _y += other._y;
}

Position Position::operator-(Position other) const
{
    return {_x - other._x, _y - other._y};
}

void Position::operator-=(Position other)
{
    _x -= other._x;
    _y -= other._y;
}

Position Position::operator*(double scalar) const
{
    return {static_cast<int>(_x * scalar), static_cast<int>(_y * scalar)};
}

void Position::operator*=(double scalar)
{
    _x *= scalar;
    _y *= scalar;
}

Position Position::operator/(double scalar) const
{
    if (scalar == 0) {
        throw std::runtime_error("Attempt to divide by 0");
    }
    return {static_cast<int>(_x / scalar), static_cast<int>(_y / scalar)};
}

void Position::operator/=(double scalar)
{
    if (scalar == 0) {
        throw std::runtime_error("Attempt to divide by 0");
    }
    _x *= scalar;
    _y *= scalar;
}

bool Position::operator==(const Position other) const
{
    if (_x == other._x && _y == other._y) {
        return true;
    }
    return false;
}

}

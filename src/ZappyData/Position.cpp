/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Position.cpp
*/

#include "include/Position.hpp"

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

Position Position::operator+(const Position &current) const
{
    Position result = *this;

    result += current;

    return result;
}

Position Position::operator+=(const Position &current)
{
    _x += current.getX();
    _y += current.getY();

    return *this;
}

Position Position::operator-(const Position &current) const
{
    Position result = *this;

    result -= current;

    return result;
}

Position Position::operator-=(const Position &current)
{
    _x -= current.getX();
    _y -= current.getY();

    return *this;
}

Position Position::operator*(const int &scalar) const
{
    Position result = *this;

    result *= scalar;

    return result;
}

Position Position::operator*=(const int &scalar)
{
    _x *= scalar;
    _y *= scalar;

    return *this;
}

Position Position::operator/(const int &scalar) const
{
    Position result = *this;

    result /= scalar;

    return result;
}

Position Position::operator/=(const int &scalar)
{
    if (scalar == 0)
        throw std::runtime_error("Attempt to divide by 0");

    _x /= scalar;
    _y /= scalar;

    return *this;
}

Position Position::operator%(const Position &other) const
{
    Position result = *this;
    result %= other;

    return result;
}

Position Position::operator%=(const Position &other)
{
    _x %= other.getX();
    _y %= other.getY();

    return *this;
}

bool Position::operator==(const Position &other) const
{
    return _x == other.getX() && _y == other.getY();
}

bool Position::operator!=(const Position &other) const
{
    return !(this == other);
}
}

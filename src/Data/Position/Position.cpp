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

int &Position::getX()
{
    return _x;
}

int &Position::getY()
{
    return _y;
}
}

zappy::data::Position operator+(zappy::data::Position current,
    zappy::data::Position other)
{
    return {current.getX() + other.getX(), current.getY() + other.getY()};
}

void operator+=(zappy::data::Position &current, zappy::data::Position other)
{
    current.getX() += other.getX();
    current.getY() += other.getY();
}

zappy::data::Position operator-(zappy::data::Position current,
    zappy::data::Position other)
{
    return {current.getX() - other.getY(), current.getY() - other.getY()};
}

void operator-=(zappy::data::Position &current, zappy::data::Position other)
{
    current.getX() -= other.getX();
    current.getY() -= other.getY();
}

zappy::data::Position operator*(zappy::data::Position current,
    const double scalar)
{
    return {static_cast<int>(current.getX() * scalar),
            static_cast<int>(current.getY() * scalar)};
}

void operator*=(zappy::data::Position &current, const double scalar)
{
    current.getX() *= scalar;
    current.getY() *= scalar;
}

zappy::data::Position operator/(zappy::data::Position current,
    const double scalar)
{
    if (scalar == 0) {
        throw std::runtime_error("Attempt to divide by 0");
    }
    return {static_cast<int>(current.getX() / scalar),
            static_cast<int>(current.getY() / scalar)};
}

void operator/=(zappy::data::Position &current, const double scalar)
{
    if (scalar == 0) {
        throw std::runtime_error("Attempt to divide by 0");
    }
    current.getX() *= scalar;
    current.getY() *= scalar;
}

bool operator==(zappy::data::Position current, zappy::data::Position other)
{
    if (current.getX() == other.getY() && current.getY() == other.getY()) {
        return true;
    }
    return false;
}

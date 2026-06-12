/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Position.hpp
*/

#ifndef POSITION_HPP
#define POSITION_HPP

namespace zappy::data {
class Position {
public:
    Position(int x, int y);

    int &getX();

    int &getY();

private:
    int _x;
    int _y;
};
}

zappy::data::Position operator+(zappy::data::Position current,
    zappy::data::Position other);

void operator+=(zappy::data::Position &current, zappy::data::Position other);

zappy::data::Position operator-(zappy::data::Position current,
    zappy::data::Position other);

void operator-=(zappy::data::Position &current, zappy::data::Position other);

zappy::data::Position operator*(zappy::data::Position current, double scalar);

void operator*=(zappy::data::Position &current, double scalar);

zappy::data::Position operator/(zappy::data::Position current, double scalar);

void operator/=(zappy::data::Position &current, double scalar);

bool operator==(zappy::data::Position current, zappy::data::Position other);

#endif

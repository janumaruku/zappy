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

    int getX() const;

    int getY() const;

    Position operator+(Position other) const;

    void operator+=(Position other);

    Position operator-(Position other) const;

    void operator-=(Position other);

    Position operator*(double scalar) const;

    void operator*=(double scalar);

    Position operator/(double scalar) const;

    void operator/=(double scalar);

    bool operator==(Position other);

private:
    int _x;
    int _y;
};
}

#endif

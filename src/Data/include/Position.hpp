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
    Position() = default;

    Position(int x, int y);

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    Position operator+(const Position &current) const;

    Position operator+=(const Position &current);

    Position operator-(const Position &current) const;

    Position operator-=(const Position &current);

    Position operator*(const int &scalar) const;

    Position operator*=(const int &scalar);

    Position operator/(const int &scalar) const;

    Position operator/=(const int &scalar);

private:
    int _x = 0;
    int _y = 0;
};
}

#endif

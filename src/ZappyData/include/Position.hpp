/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Position.hpp
*/

#ifndef POSITION_HPP
#define POSITION_HPP
#include <cstdint>

namespace zappy::data {
enum class Orientation: uint8_t {
    UP = 0,
    RIGHT,
    DOWN,
    LEFT,
};

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

    Position operator%(const Position &other) const;

    Position operator%=(const Position &other);

    bool operator==(const Position &other) const;
    
    bool operator!=(const Position &other) const;


private:
    int _x = 0;
    int _y = 0;
};
}

#endif

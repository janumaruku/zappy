/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Grid
*/

#ifndef GRID_HPP
#define GRID_HPP

namespace zappy::gui {
class Grid {
public:
    Grid(const int &width, const int &height);

    void render() const;

private:
    int _width;
    int _height;
};
}

#endif //GRID_HPP

/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include "Player.hpp"

namespace zappy::server {

class Map {
public:
    explicit Map(const int width, const int height);

    ~Map() = default;

    [[nodiscard]] int getWidth() const noexcept;
    [[nodiscard]] int getHeight() const noexcept;
    [[nodiscard]] const data::Tile &getTile(const data::Position &pos) const;
    [[nodiscard]] const Player &getPlayer(const PlayerId &id) const;
    void generate();
    void generateResource(const data::Resource &resource, uint amount);
    [[nodiscard]] bool takeResource(const data::Resource &resource,
        const data::Position &pos);
    void dropResource(const data::Resource &resource,
        const data::Position &pos);

private:
    int _width;
    int _height;
    std::vector<data::Tile> _tiles;
    std::unordered_map<PlayerId, Player> _players;
};

}

#endif

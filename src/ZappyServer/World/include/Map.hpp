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
#include <memory>

#include "Player.hpp"
#include "Egg.hpp"

namespace zappy::server {

class Map {
public:
    explicit Map(const int width, const int height);

    ~Map() = default;

    [[nodiscard]] int getWidth() const noexcept;
    [[nodiscard]] int getHeight() const noexcept;
    [[nodiscard]] const data::Tile &getTile(const data::Position &pos) const;
    [[nodiscard]] const Player &getPlayer(const PlayerId &id) const;
    [[nodiscard]] Player &getPlayer(const PlayerId &id);
    [[nodiscard]] const std::unordered_map<PlayerId, Player> &getPlayers() const noexcept;
    Player &spawnPlayer(const PlayerId &id, const TeamId &team);
    [[nodiscard]] bool hasPlayer(const PlayerId &id) const noexcept;
    void generate();
    void generateResource(const data::Resource &resource, uint amount);
    [[nodiscard]] bool takeResource(const data::Resource &resource,
        const data::Position &pos);
    void dropResource(const data::Resource &resource,
        const data::Position &pos);

    void addEgg(const data::Egg &egg);
    void removeEgg(const uint &eggId);
    [[nodiscard]] const std::unordered_map<uint, data::Egg> &getEggs() const noexcept;
    [[nodiscard]] std::unique_ptr<std::vector<uint>> getEggsOnTile(const data::Position &pos) const;

private:
    int _width;
    int _height;
    std::vector<data::Tile> _tiles;
    std::unordered_map<PlayerId, Player> _players;
    std::unordered_map<uint, data::Egg> _eggs;
    uint _nextEggId = 1;
};

}

#endif

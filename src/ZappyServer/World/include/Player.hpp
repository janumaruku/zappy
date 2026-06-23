/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <cstdint>
    #include <string>
    #include <unordered_map>
    #include "Position.hpp"
    #include "Tile.hpp"

namespace zappy::server {

using PlayerId = std::string;
using TeamId = std::string;

class Player {
public:
    Player() = delete;
    explicit Player(const PlayerId &id, const TeamId &team,
        const data::Position &position, const std::uint8_t &level, uint mapWidth, uint mapHeight);

    void left();
    void forward();
    void right();
    void takeResource(const data::Resource &resource);
    bool removeResource(const data::Resource &resource);

    [[nodiscard]] PlayerId getId() const noexcept;
    [[nodiscard]] TeamId getTeam() const noexcept;
    [[nodiscard]] data::Position getPosition() const noexcept;
    [[nodiscard]] std::uint8_t getLevel() const noexcept;
    [[nodiscard]] data::Orientation getOrientation() const noexcept;
    [[nodiscard]] const std::unordered_map<data::Resource, std::uint8_t> &getInventory() const noexcept;

private:
    PlayerId _id;
    TeamId _team;
    data::Position _position;
    std::uint8_t _level;
    std::unordered_map<data::Resource, std::uint8_t> _inventory;
    data::Orientation _orientation;
    uint _mapWidth;
    uint _mapHeight;
};

} // namespace zappy::server

#endif

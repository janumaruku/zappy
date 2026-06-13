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
    #include "Data.hpp"
    #include "Resources.hpp"

namespace zappy::server {

using PlayerId = std::string;
using TeamId = std::string;

class Player {
public:
    Player() = delete;
    explicit Player(const PlayerId &id, const TeamId &team,
        const zappy::data::Position &position, const std::uint8_t &level);

    void left();
    void forward();
    void right();
    bool eatFood();
    bool takeResource(const Resource &resource);

    [[nodiscard]] const PlayerId &getId() const;
    [[nodiscard]] const TeamId &getTeam() const;
    [[nodiscard]] const zappy::data::Position &getPosition() const;
    [[nodiscard]] const std::uint8_t &getLevel() const;

private:
    PlayerId _id;
    TeamId _team;
    zappy::data::Position _position;
    std::uint8_t _level;
    std::unordered_map<Resource, std::uint8_t> _inventory;

    enum Direction : std::uint8_t {
        UP,
        LEFT,
        DOWN,
        RIGHT,
    } _orientation;
};

} // namespace zappy::server

#endif

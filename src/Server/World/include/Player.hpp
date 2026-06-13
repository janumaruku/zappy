/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** Player.hpp
*/

#pragma once

#include <string>
#include <unordered_map>
#include <stdint.h>
#include "Map.hpp"

namespace zappy::server {

class Player {
public:

    Player() = delete;
    explicit Player(const PlayerId &id, const TeamId &team, const zappy::data::Position &position, const std::uint8_t &level);
    
    void left();
    void forward();
    void right();
    bool eatFood();
    bool takeResource(const Resource& resource);

    [[nodiscard]] const PlayerId &getId() const;
    [[nodiscard]] const TeamId &getTeam() const;
    [[nodiscard]] const zappy::data::Position &getPosition() const;
    [[nodiscard]] const std::uint8_t &getLevel() const;

private:

    PlayerId _id;
    TeamId _team;
    zappy::data::Position _position;
    std::uint8_t _level;
    std::unordered_map<std::uint8_t, Resource> _inventory;

    enum Direction : std::uint8_t {
        UP,
        LEFT,
        DOWN
        RIGHT,
    } _orientation;
};

}
/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Team.hpp
*/

#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <raylib.h>
#include <string>
#include <vector>

namespace zappy::gui {
class Team {
public:
    using PlayerId = std::string;

    explicit Team(const std::string &name, const Color &color);

    std::string getName() const;

    [[nodiscard]] Color getColor() const;

    [[nodiscard]] std::vector<PlayerId> getPlayers() const;

    void addPlayer(const PlayerId &id);

    void removePlayer(const PlayerId &id);

private:
    std::string _name;
    std::vector<PlayerId> _players;
    Color _color;
};
}

#endif

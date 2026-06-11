/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Team.hpp
*/

#ifndef TEAM_HPP_
#define TEAM_HPP_
#include <list>
#include <string>

namespace zappy::gui {
class Team {
public:
    using PlayerId = std::string;

    Team(std::string name/*, Color color*/);

    std::string getName();

    /*Color getColor();*/

    void addPlayer(PlayerId id);

    void removePlayer(PlayerId id);

private:
    std::string _name;
    std::list<PlayerId> _players;
    /*Color _color;*/
};
}

#endif

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState
*/

#include "WorldState.hpp"

#include <iostream>

namespace zappy::gui {
WorldState::WorldState(const GUIMap &map,
    const std::unordered_map<std::string, Team> &teams,
    const uint timeUnit): _map(map), _teams(teams), _timeUnit(timeUnit)
{

}

GUIMap WorldState::getMap() const
{
    return _map;
}

std::unordered_map<PlayerId, GUIPlayer> WorldState::getPlayers()
{
    return _players;
}

GUIPlayer &WorldState::getPlayerById(const PlayerId &id)
{

    if (!_players.contains(id)) {
        throw std::runtime_error("Player not found: " + id);
    }
    return _players.at(id);
}

const std::unordered_map<std::string, Team> &WorldState::getTeams()
{
    return _teams;
}

void WorldState::onPlayerNew(const PlayerId &id, data::Position position,
    const Orientation orientation, const uint8_t level, const std::string &team)
{
    if (position.getX() > static_cast<int>(_map.getWidth()) || position.
        getX() < 0 || position.getY() > static_cast<int>(_map.getHeight()) ||
        position.getY() < 0) {
        std::cerr << "New player out of bound" << std::endl;
        return;
    }
    if (!_teams.contains(team)) {
        std::cerr << team << " is not found" << std::endl;
        return;
    }
    _teams.at(team).addPlayer(id);
    _players.emplace(id, GUIPlayer(id, team, position, orientation, level));
    std::clog << "New Player " << id << " has joined" << std::endl;
}

/*void WorldState::onPlayerPosition(Position pos, Orientation orientation){

}*/

void WorldState::onPlayerDeath(const PlayerId &id)
{
    if (!_players.contains(id)) {
        std::cerr << "Player " << id << " is not found " << std::endl;
        return;
    }
    _players.erase(id);
    _teams.at(_players.at(id).getTeam()).removePlayer(id);
}

/*void WorldState::onTileContent(Position pos, std::map<Resource, uint> resources){

}*/

/*void WorldState::onTimeUnit(uint t)
{
    (void)t;
}*/

uint WorldState::getTimeUnit() const
{
    return _timeUnit;
}

/*void WorldState::onEggLaid(uint eggId, PlayerId playerId, Position pos){

}*/

void WorldState::onEggDeath(const uint eggId)
{
    if (!_eggs.contains(eggId)) {
        std::cerr << eggId << " is not found onEggDeath" << std::endl;
        return;
    }
    _eggs.erase(eggId);
}
}

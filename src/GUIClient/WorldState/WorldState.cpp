/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState
*/

#include "WorldState.hpp"

#include <iostream>

namespace zappy::gui {
WorldState::WorldState(const GUIMap &map, const uint timeUnit): _map(map),
    _timeUnit(timeUnit)
{

}

GUIMap WorldState::getMap() const
{
    return _map;
}

std::map<PlayerId, GUIPlayer> WorldState::getPlayers()
{
    return _players;
}

GUIPlayer WorldState::getPlayer(const PlayerId &id)
{
    auto it = _players.find(id);

    if (it == _players.end()) {
        throw std::runtime_error("Player not found: " + id);
    }
    return it->second;
}

std::map<std::string, Team> WorldState::getTeams()
{
    return _teams;
}

void WorldState::onPlayerNew(PlayerId id, data::Position position,
    const Orientation orientation, const uint8_t level, std::string team)
{
    if (position.getX() > static_cast<int>(_map.getWidth()) || position.
        getX() < 0 || position.getY() > static_cast<int>(_map.getHeight()) ||
        position.getY() < 0) {
        std::cerr << "new player out of bound" << std::endl;
        return;
    }
    const auto it = _teams.find(team);

    if (it == _teams.end()) {
        const auto newIt = _teams.insert({team, Team(team)}).first;
        newIt->second.addPlayer(id);
    } else {
        it->second.addPlayer(id);
    }
    _players.insert({id, GUIPlayer(id, team, position, orientation, level)});
    std::clog << "New Player " << id << " has joined" << std::endl;
}

/*void WorldState::onPlayerPosition(Position pos, Orientation orientation){

}*/

void WorldState::onPlayerDeath(const PlayerId &id)
{
    auto player = _players.find(id);
    if (player == _players.end()) {
        std::cerr << "Player not found onPlayerDeath" << std::endl;
        return;
    }
    const std::string team = player->second.getTeam();
    auto it = _teams.find(team);

    if (it == _teams.end()) {
        std::cerr << "Team not found onPlayerDeath" << std::endl;
        return;
    }
    it->second.removePlayer(id);
    _players.erase(player);
    std::clog << "Player " << id << " is dead" << std::endl;
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
    const auto it = _eggs.find(eggId);

    if (it == _eggs.end()) {
        std::cerr << eggId << " is not found onEggDeath" << std::endl;
        return;
    }
    _eggs.erase(eggId);
}
}

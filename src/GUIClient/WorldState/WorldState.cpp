/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState
*/

#include "WorldState.hpp"

#include <iostream>
#include <stdexcept>

namespace zappy::gui {

constexpr uint PLACEHOLDER_MAP_DIMENSION = 10;

WorldState::WorldState(const std::unordered_map<std::string, Team> &teams,
    const uint timeUnit): _teams(teams),_timeUnit(timeUnit)
{
    // need to change this to a real map size
    _map = GUIMap(PLACEHOLDER_MAP_DIMENSION, PLACEHOLDER_MAP_DIMENSION);
}

const GUIMap &WorldState::getMap() const
{
    return _map;
}

const std::unordered_map<PlayerId, GUIPlayer> &WorldState::getPlayers()
{
    return _players;
}

const GUIPlayer &WorldState::getPlayerById(const PlayerId &id)
{

    if (!_players.contains(id))
        throw std::runtime_error("Player not found: " + id);
    return _players.at(id);
}

const std::unordered_map<std::string, Team> &WorldState::getTeams()
{
    return _teams;
}

void WorldState::onPlayerNew(const GUIPlayer &player)
{
    auto playerPos = player.getPosition();
    if (playerPos.getX() > static_cast<int>(_map.getWidth()) ||
        playerPos.getX() < 0 ||
        playerPos.getY() > static_cast<int>(_map.getHeight()) ||
        playerPos.getY() < 0) {
            throw std::out_of_range("Player position is out of map bounds");
    }
    if (!_teams.contains(player.getTeam()))
        throw std::runtime_error("Team not found: " + player.getTeam());

    _teams.at(player.getTeam()).addPlayer(player.getId());
    _players.emplace(player.getId(), player);
    std::clog << "New Player " << player.getId() << " has joined" << std::endl;
}

/*void WorldState::onPlayerPosition(Position pos, Orientation orientation){

}*/

void WorldState::onPlayerDeath(const PlayerId &id)
{
    if (!_players.contains(id))
        throw std::runtime_error("Player not found: " + id);
    _teams.at(_players.at(id).getTeam()).removePlayer(id);
    _players.erase(id);
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

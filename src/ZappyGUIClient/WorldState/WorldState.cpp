/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState
*/

#include "WorldState.hpp"

#include <iostream>

namespace zappy::gui {
WorldState::WorldState(const std::unordered_map<std::string, Team> &teams,
    const int timeUnit, const int width, const int height): _map{width, height},
    _teams(teams), _timeUnit(timeUnit)
{
}

const GUIMap &WorldState::getMap() const noexcept
{
    return _map;
}

const std::unordered_map<WorldState::PlayerId, GUIPlayer> &
WorldState::getPlayers() const noexcept
{
    return _players;
}

const GUIPlayer &WorldState::getPlayerById(const PlayerId &id) const
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

void WorldState::onPlayerNew(GUIPlayer player)
{
    _players.emplace(player.getId(), player);
    std::clog << "New Player " << player.getId() << " has joined" << std::endl;
}

void WorldState::onPlayerPosition(const std::string &id,
    const data::Position &pos, const data::Orientation &orientation)
{
    auto &player = _players.at(id);
    player.setOrientation(orientation);
    player.setPosition(pos);
}

void WorldState::onPlayerDeath(const PlayerId &id)
{
    if (!_players.contains(id)) {
        std::cerr << "Player " << id << " is not found " << std::endl;
        return;
    }

    const auto player = _players.at(id);
    _teams.at(player.getTeam()).removePlayer(id);
    _players.erase(id);
}

void WorldState::onTileContent(const data::Position pos,
    const std::unordered_map<data::Resource, int> &resources)
{
    _map.updateTile(pos, resources);
}

/*void WorldState::onTimeUnit(int t)
{
    (void)t;
}*/

int WorldState::getTimeUnit() const
{
    return _timeUnit;
}

/*void WorldState::onEggLaid(int eggId, PlayerId playerId, Position pos){

}*/

void WorldState::onEggDeath(const int eggId)
{
    if (!_eggs.contains(eggId)) {
        std::cerr << eggId << " is not found onEggDeath" << std::endl;
        return;
    }
    _eggs.erase(eggId);
}

void WorldState::onMapDimension(const int &width, const int &height)
{
    _map.updateWidth(width);
    _map.updateHeight(height);
}
}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState
*/

#include "WorldState.hpp"

#include <algorithm>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include "GUIPlayer.hpp"
#include "Position.hpp"
#include "Team.hpp"
#include "ZappyEvents.hpp"

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

GUIPlayer &WorldState::getPlayerById(PlayerId id)
{

    if (!_players.contains(id))
        throw std::runtime_error("Player not found: " + id);
    return _players.at(id);
}

const std::unordered_map<std::string, Team> &WorldState::getTeams()
    const noexcept
{
    return _teams;
}

void WorldState::onPlayerNew(const GUIPlayer &player)
{
    if (_teams.contains(player.getTeam()))
        _teams.at(player.getTeam()).addPlayer(player.getId());
    _players.emplace(player.getId(), player);
    std::clog << "New Player " << player.getId() << " has joined" << std::endl;

    notify(ZappyEventType::GUI_EVENT, PlayerNewEvent{player});
}

void WorldState::onPlayerLevel(const GUIPlayer &player)
{
    if (! _teams.contains(player.getTeam()))
        return;
    notify(ZappyEventType::GUI_EVENT, PlayerLevelEvent{player});
}

static bool hasMovedClockwise(const data::Orientation &old, const data::Orientation &other)
{
    if (old == data::Orientation::UP && other == data::Orientation::RIGHT)
        return true;
    if (old == data::Orientation::RIGHT && other == data::Orientation::DOWN)
        return true;
    if (old == data::Orientation::DOWN && other == data::Orientation::LEFT)
        return true;
    if (old == data::Orientation::LEFT && other == data::Orientation::UP)
        return true;
    return false;
}

static bool hasMovedCounterClockwise(const data::Orientation &old, const data::Orientation &other)
{
    if (old == data::Orientation::UP && other == data::Orientation::LEFT)
        return true;
    if (old == data::Orientation::LEFT && other == data::Orientation::DOWN)
        return true;
    if (old == data::Orientation::DOWN && other == data::Orientation::RIGHT)
        return true;
    if (old == data::Orientation::RIGHT && other == data::Orientation::UP)
        return true;
    return false;
}

void WorldState::onPlayerPosition(const std::string &id,
    const data::Position &pos, const data::Orientation &orientation)
{
    auto &player = _players.at(id);
    const auto &oldPos = player.getPosition();
    const auto &oldOrient = player.getOrientation();
    ActionType a;

    if (oldPos != pos)
        a = ActionType::FORWARD;
    if (hasMovedClockwise(oldOrient, orientation))
        a = ActionType::RIGHT;
    if (hasMovedCounterClockwise(oldOrient, orientation))
        a = ActionType::LEFT;

    player.setOrientation(orientation);
    player.setPosition(pos);

    Action action{.type=a, .duration=7.0F / static_cast<float>(_timeUnit)};

    notify(ZappyEventType::GUI_EVENT, PlayerMovedEvent{player});
    player.enqueueAction(action);

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

    notify(ZappyEventType::GUI_EVENT, PlayerDiedEvent{id});
}

void WorldState::onTileContent(const data::Position pos,
    const std::unordered_map<data::Resource, int> &resources)
{
    _map.updateTile(pos, resources);

    notify(ZappyEventType::GUI_EVENT, TileUpdateEvent{
        .position = pos,
        .resources = resources
    });
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

void WorldState::onEggHatched(const uint &id)
{
    auto idStr = std::to_string(id);
    const auto it = _eggs.find(idStr);

    if (it != _eggs.end())
        _eggs.erase(it);
}

void WorldState::onEggDeath(const std::string& eggId)
{
    if (!_eggs.contains(eggId)) {
        std::cerr << eggId << " is not found onEggDeath" << std::endl;
        return;
    }
    _eggs.erase(eggId);

    notify(ZappyEventType::GUI_EVENT, EggDiedEvent{eggId});
}

void WorldState::onMapDimension(const int &width, const int &height)
{
    _map.updateWidth(width);
    _map.updateHeight(height);
}

void WorldState::onIncantationStart(const data::Position &pos, const uint &level, const std::vector<PlayerId> &playerIds)
{
    IncantationStartEvent i(pos, level, playerIds);
    notify(ZappyEventType::GUI_EVENT, i);
}

void WorldState::onIncantationEnd(const data::Position &pos, bool result)
{
    IncantationEndEvent e(pos, result);
    notify(ZappyEventType::GUI_EVENT, e);
}

void WorldState::onGameEnd(const Team &winningTeam)
{
    _winner = winningTeam.getName();
    GameEndEvent evt(winningTeam.getName());
    notify(ZappyEventType::GUI_EVENT, evt);
}

const std::optional<std::string> &WorldState::getWinner() const
{
    return _winner;
}

}

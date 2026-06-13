/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState.hpp
*/

#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP
#include <string>
#include <unordered_map>
#include <sys/types.h>

#include "GUIEgg.hpp"
#include "GUIMap.hpp"
#include "GUIPlayer.hpp"
#include "Team.hpp"

namespace zappy::gui {

constexpr uint DEFAULT_TIME_UNIT = 1;

class WorldState {
    using PlayerId = std::string;

public:
    WorldState(const std::unordered_map<std::string, Team> &teams, uint timeUnit);

    const GUIMap &getMap() const;

    const std::unordered_map<PlayerId, GUIPlayer> &getPlayers();

    const GUIPlayer &getPlayerById(const PlayerId &id);

    const std::unordered_map<std::string, Team> &getTeams();

    uint getTimeUnit() const;

    void onPlayerNew(const GUIPlayer &player);

    //void onPlayerPosition(Position pos, Orientation orientation);

    void onPlayerDeath(const PlayerId &id);

    //void onTileContent(Position pos, map<Resource, uint> resources);

    void onTimeUnit(uint t);

    //void onEggLaid(uint eggId, PlayerId playerId, Position pos);

    void onEggDeath(uint eggId);

private:
    GUIMap _map;
    std::unordered_map<PlayerId, GUIPlayer> _players;
    std::unordered_map<uint, GUIEgg> _eggs;
    std::unordered_map<std::string, Team> _teams;
    uint _timeUnit = DEFAULT_TIME_UNIT;
};
}

#endif

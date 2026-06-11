/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState.hpp
*/

#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP
#include <map>
#include <string>
#include <sys/types.h>

#include "GUIEgg.hpp"
#include "GUIMap.hpp"
#include "GUIPlayer.hpp"
#include "Team.hpp"

namespace zappy::gui {
class WorldState {
    using PlayerId = std::string;

public:
    WorldState(const GUIMap &map, uint timeUnit);

    GUIMap getMap() const;

    std::map<PlayerId, GUIPlayer> getPlayers();

    GUIPlayer getPlayer(const PlayerId &id);

    std::map<std::string, Team> getTeams();

    uint getTimeUnit() const;

    void onPlayerNew(PlayerId id, data::Position position,
        Orientation orientation,
        uint8_t level, std::string team);

    //void onPlayerPosition(Position pos, Orientation orientation);

    void onPlayerDeath(const PlayerId &id);

    //void onTileContent(Position pos, map<Resource, uint> resources);

    void onTimeUnit(uint t);

    //void onEggLaid(uint eggId, PlayerId playerId, Position pos);

    void onEggDeath(uint eggId);

private:
    GUIMap _map;
    std::map<PlayerId, GUIPlayer> _players;
    std::map<uint, GUIEgg> _eggs;
    std::map<std::string, Team> _teams;
    uint _timeUnit = 0;
};
}

#endif

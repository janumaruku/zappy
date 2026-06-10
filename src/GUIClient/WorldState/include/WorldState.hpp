/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState.hpp
*/

#ifndef WORLDSTATE_HPP_
#define WORLDSTATE_HPP_
#include <sys/types.h>

namespace zappy::gui {
class WorldState {
public:
    //GUIMap getMap();
    //map<PlayerId, GUIPlayer> getPlayers();
    //GUIPlayer getPlayer(Playerid id);
    //map<string, Team> getTeams();
    uint getTimeUnit() const;

    //void onPlayerNew(PlayerId id, Position pos, Orientation orientation, uint8 level, std::string team);
    //void onPlayerPosition(Position pos, Orientation orientation);
    //void onPlayerDeath(PlayerId id);
    //void onTileContent(Position pos, map<Resource, uint> resources);
    void onTimeUnit(uint t);

    //void onEggLaid(uint eggId, PlayerId playerId, Position pos);
    void onEggDeath(uint eggId);

private:
    //GUIMap _map;
    //map<PlayerId, GUIPlayer> _players;
    //map<uint, GUIEgg> _eggs;
    //map<string, Team> _teams;
    uint _timeUnit = 0;
};
}

#endif

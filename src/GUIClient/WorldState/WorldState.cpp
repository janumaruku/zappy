/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState
*/

#include "WorldState.hpp"

//GUIMap getMap(){
//  return _map;
//}

//map<PlayerId, GUIPlayer> getPlayers(){
//
//}

//GUIPlayer getPlayer(PlayerId id){
//return _player.find(id);
//}

//map<string, Team> getTeams(){
//return _teams;
//}

//void onPlayerNew(PlayerId id, Position pos, Orientation orientation, uint8 level, std::string team){
//
//}

//void onPlayerPosition(Position pos, Orientation orientation){
//
//}

//void onPlayerDeath(PlayerId id){
//
//}

//void onTileContent(Position pos, map<Resource, uint> resources){
//
//}

void onTimeUnit(uint t)
{
    (void)t;
}

uint zappy::gui::WorldState::getTimeUnit() const
{
    return _timeUnit;
}

//void onEggLaid(uint eggId, PlayerId playerId, Position pos){
//
//}

void onEggDeath(uint eggId)
{
    (void)eggId;
}

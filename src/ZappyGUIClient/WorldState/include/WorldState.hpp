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

#include "Egg.hpp"
#include "GUIMap.hpp"
#include "GUIPlayer.hpp"
#include "Team.hpp"

namespace zappy::gui {
class WorldState {
    using PlayerId = std::string;

public:
    WorldState() = default;
    WorldState(const std::unordered_map<std::string, Team> &teams,
        uint timeUnit, uint width, uint height);

    [[nodiscard]] const GUIMap &getMap() const noexcept;

    const std::unordered_map<PlayerId, GUIPlayer> &getPlayers() const noexcept;

    const GUIPlayer &getPlayerById(const PlayerId &id) const;

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
    std::unordered_map<uint, data::Egg> _eggs;
    std::unordered_map<std::string, Team> _teams;
    uint _timeUnit = 1;
};
}

#endif

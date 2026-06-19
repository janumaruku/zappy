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
        int timeUnit, int width, int height);

    [[nodiscard]] const GUIMap &getMap() const noexcept;

    const std::unordered_map<PlayerId, GUIPlayer> &getPlayers() const noexcept;

    const GUIPlayer &getPlayerById(const PlayerId &id) const;

    const std::unordered_map<std::string, Team> &getTeams();

    int getTimeUnit() const;

    void onPlayerNew(GUIPlayer player);

    void onPlayerPosition(const std::string &id, const data::Position &pos,
        const data::Orientation &orientation);

    void onPlayerDeath(const PlayerId &id);

    void onTileContent(data::Position pos,
        const std::unordered_map<data::Resource, int> &resources);

    void onTimeUnit(int t);

    //void onEggLaid(int eggId, PlayerId playerId, Position pos);

    void onEggDeath(int eggId);

    void onMapDimension(const int &width, const int &height);

private:
    GUIMap _map;
    std::unordered_map<PlayerId, GUIPlayer> _players;
    std::unordered_map<int, data::Egg> _eggs;
    std::unordered_map<std::string, Team> _teams;
    int _timeUnit = 1;
};
}

#endif

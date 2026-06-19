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
#include <variant>
#include <sys/types.h>

#include "ASubject.hpp"
#include "Egg.hpp"
#include "GUIMap.hpp"
#include "GUIPlayer.hpp"
#include "Team.hpp"

namespace zappy::gui {
enum class GUIEventType: std::uint8_t {
    PLAYER_NEW,
    PLAYER_MOVE,
    PLAYER_DIED,
    TILE_UPDATE,
    EGG_LAID,
    EGG_HATCHED,
    EGG_DIED,
    INCANTATION_START,
    INCANTATION_END,
    GAME_END
};

using GUIEvent = std::variant<int>;

class WorldState: designPattern::ASubject<GUIEvent, GUIEventType> {
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

    void onPlayerNew(GUIPlayer player);

    void onPlayerPosition(const std::string &id, const data::Position &pos,
        const data::Orientation &orientation);

    void onPlayerDeath(const PlayerId &id);

    void onTileContent(data::Position pos,
        const std::unordered_map<data::Resource, uint> &resources);

    void onTimeUnit(uint t);

    //void onEggLaid(uint eggId, PlayerId playerId, Position pos);

    void onEggDeath(uint eggId);

    void onMapDimension(const uint &width, const uint &height);

private:
    GUIMap _map;
    std::unordered_map<PlayerId, GUIPlayer> _players;
    std::unordered_map<uint, data::Egg> _eggs;
    std::unordered_map<std::string, Team> _teams;
    uint _timeUnit = 1;
};
}

#endif

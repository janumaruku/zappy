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

#include "ASubject.hpp"
#include "Egg.hpp"
#include "GUIMap.hpp"
#include "GUIPlayer.hpp"
#include "Team.hpp"
#include "ZappyEvents.hpp"

namespace zappy::gui {
enum class ZappyEventType: std::uint8_t {
    GUI_EVENT,
};

class WorldState: designPattern::ASubject<ZappyEvent, ZappyEventType> {
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

    void onEggDeath(const std::string& eggId);

    void onMapDimension(const uint &width, const uint &height);

private:
    GUIMap _map;
    std::unordered_map<PlayerId, GUIPlayer> _players;
    std::unordered_map<std::string, data::Egg> _eggs;
    std::unordered_map<std::string, Team> _teams;
    uint _timeUnit = 1;
};
}

#endif

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** WorldState.hpp
*/

#ifndef WORLDSTATE_HPP
#define WORLDSTATE_HPP
#include <optional>
#include <string>
#include <unordered_map>
#include <sys/types.h>
#include <vector>

#include "ASubject.hpp"
#include "Egg.hpp"
#include "GUIMap.hpp"
#include "GUIPlayer.hpp"
#include "Position.hpp"
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
        int timeUnit, int width, int height);

    [[nodiscard]] const GUIMap &getMap() const noexcept;

    const std::unordered_map<PlayerId, GUIPlayer> &getPlayers() const noexcept;

    const GUIPlayer &getPlayerById(const PlayerId &id) const;

    const std::unordered_map<std::string, Team> &getTeams() const noexcept;

    int getTimeUnit() const;

    void onPlayerNew(GUIPlayer player);

    void onPlayerPosition(const std::string &id, const data::Position &pos,
        const data::Orientation &orientation);

    void onPlayerDeath(const PlayerId &id);

    void onTileContent(data::Position pos,
        const std::unordered_map<data::Resource, int> &resources);

    void onTimeUnit(int t);

    void onEggLaid(int eggId, PlayerId playerId, data::Position pos);
    void onEggDeath(const std::string& eggId);
    void onEggHatched(const uint &id);

    void onMapDimension(const int &width, const int &height);

    void onIncantationStart(const data::Position &pos, const uint &level, const std::vector<PlayerId> &playerIds);
    void onIncantationEnd(const data::Position &pos, bool result);

    void onGameEnd(const Team &winningTeam);

    const std::optional<std::string> &getWinner() const;

private:
    GUIMap _map;
    std::unordered_map<PlayerId, GUIPlayer> _players;
    std::unordered_map<std::string, data::Egg> _eggs;
    std::unordered_map<std::string, Team> _teams;
    std::optional<std::string> _winner = std::nullopt;
    int _timeUnit = 1;
};
}

#endif

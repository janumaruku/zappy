/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Server
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

#include "Acceptor.hpp"
#include "ConnectedSocket.hpp"
#include "IoContext.hpp"
#include "GUIProtocolHandler.hpp"
#include "Map.hpp"
#include "Timer.hpp"

namespace zappy::server {

class AISession;
class GUISession;

class Server {
public:
    explicit Server(int port, int width, int height,
        std::vector<std::string> teams, uint playersPerTeam,
        uint frequency = 1);
    ~Server();

    void run();

    void notifyGUI(const std::string &command);
    bool handleGUICommand(GUISession &session, const std::string &command,
        const std::vector<std::string> &args = {});
    [[nodiscard]] std::optional<std::string> checkWinCondition() const noexcept;
    void stop() noexcept;
    void broadcastToAll(const std::string &data);
    void forEachAISession(const std::function<void(AISession &)> &fn);

    [[nodiscard]] const uint &getFrequency() const;
    void setFrequency(uint frequency) noexcept;
    [[nodiscard]] const Map &getMap() const noexcept { return _map; }
    [[nodiscard]] Map &getMap() noexcept { return _map; }
    [[nodiscard]] const std::vector<std::string> &getTeams() const noexcept { return _teams; }

private:
    static constexpr uint RESOURCE_RESPAWN_TIME_UNIT = 20;

    network::IOContext _ioContext;
    network::Acceptor _acceptor;
    std::vector<std::string> _teams;
    uint _frequency = 1;
    uint _nextPlayerId = 1;
    std::unordered_map<std::string, uint> _availableSlots;
    GUIProtocolHandler _guiProtocolHandler;

    Map _map;
    SteadyTimer _resourceRespawnTimer;
    std::vector<std::unique_ptr<AISession>> _aiSessions;
    std::vector<std::unique_ptr<GUISession>> _guiSessions;

    void startAccept();

    void onAccept(
        std::shared_ptr<network::ConnectedSocket> socket
        );
    void onPlayerMoved(const Player &player);

    void handleAiHandshake(const std::shared_ptr<network::ConnectedSocket> &socket,
        const std::string &teamName);
    void handleGuiHandshake(const std::shared_ptr<network::ConnectedSocket> &socket);
    void scheduleResourceRespawn();
    void respawnResources();
    void notifyMapContent();
    void sendMapContent(GUISession &session);
    [[nodiscard]] std::string makePlayerId();
};
}

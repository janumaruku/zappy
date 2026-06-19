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

#include "Acceptor.hpp"
#include "ConnectedSocket.hpp"
#include "IoContext.hpp"
#include "GUIProtocolHandler.hpp"
#include "Map.hpp"

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

    void notifyGUI(const std::string &command,
        const std::vector<std::string> &args = {});
    void broadcastToAll(const std::string &data);

    [[nodiscard]] const uint &getFrequency() const;
    [[nodiscard]] const Map &getMap() const noexcept { return _map; }
    [[nodiscard]] Map &getMap() noexcept { return _map; }
    [[nodiscard]] const std::vector<std::string> &getTeams() const noexcept { return _teams; }

private:
    network::IOContext _ioContext;
    network::Acceptor _acceptor;
    std::vector<std::string> _teams;
    uint _frequency = 1;
    uint _nextPlayerId = 1;
    std::unordered_map<std::string, uint> _availableSlots;
    GUIProtocolHandler _guiProtocolHandler;

    Map _map;
    std::vector<std::unique_ptr<AISession>> _aiSessions;
    std::vector<std::unique_ptr<GUISession>> _guiSessions;

    void startAccept();

    void onAccept(
        const std::shared_ptr<network::ConnectedSocket> &socket
        );
    void handleAiHandshake(const std::shared_ptr<network::ConnectedSocket> &socket,
        const std::string &teamName);
    void handleGuiHandshake(const std::shared_ptr<network::ConnectedSocket> &socket);
    [[nodiscard]] std::string makePlayerId();
};
}

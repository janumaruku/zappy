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

#include "Acceptor.hpp"
#include "ConnectedSocket.hpp"
#include "IoContext.hpp"
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

    void notifyGUI(const std::string &message);
    void broadcastToAll(const std::string &data);

    [[nodiscard]] const uint &getFrequency() const;

private:
    network::IOContext _ioContext;
    network::Acceptor _acceptor;
    std::vector<std::string> _teams;
    uint _frequency = 1;

    Map _map;
    std::vector<std::unique_ptr<AISession>> _aiSessions;
    std::vector<std::unique_ptr<GUISession>> _guiSessions;

    void startAccept();

    void onAccept(
        const std::shared_ptr<network::ConnectedSocket> &socket
        );
};
}

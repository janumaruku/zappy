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

namespace zappy::server {

class Map;
class AISession;
class GUISession;
class Server {
public:
    explicit Server(int port);

    void run();

    void notifyGUI(const std::string &message);
    void broadcastToAll(const std::string &data);

private:
    network::IOContext _ioContext;
    network::Acceptor _acceptor;

    // Map *_map = nullptr; //PR needs to switch type from pointer to value
    std::vector<AISession *> _aiSessions; //PR needs to switch type from pointer to value
    std::vector<GUISession *> _guiSessions; //PR needs to switch type from pointer to value

    void startAccept();

    void onAccept(
        const std::shared_ptr<network::ConnectedSocket> &socket
        );

    void aiHandshake(
        const std::shared_ptr<network::ConnectedSocket> &socket,
        const std::string &teamName
    );

    void guiHandshake(
        const std::shared_ptr<network::ConnectedSocket> &socket
    );
};
}

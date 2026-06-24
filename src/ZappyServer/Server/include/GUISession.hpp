/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#pragma once

#include "AClientSession.hpp"

namespace zappy::server {

class Server;

class GUISession: public AClientSession {
public:
    GUISession(const std::shared_ptr<network::ConnectedSocket> &socket,
        Server &server);
    ~GUISession() override = default;

    [[nodiscard]] const Server &getServer() const noexcept;
    [[nodiscard]] Server &getServer() noexcept;

protected:
    Server &_server;

    void handleTransmission() override;
};

}

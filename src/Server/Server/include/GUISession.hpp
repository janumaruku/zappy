/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef GUISESSION_HPP_
#define GUISESSION_HPP_

#include "AClientSession.hpp"
#include "Server.hpp"

namespace zappy::server {

class GUISession: public AClientSession {
public:
    GUISession(const std::shared_ptr<network::ConnectedSocket> &socket,
        Server &server);
    ~GUISession() override = default;

protected:
    Server &_server;

    void handleTransmission(const std::size_t &bytes) override;
};

}

#endif

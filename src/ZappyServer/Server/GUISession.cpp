/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "GUISession.hpp"

namespace zappy::server {

GUISession::GUISession(const std::shared_ptr<network::ConnectedSocket> &socket,
    Server &server): AClientSession{socket}, _server{server}
{
}

const Server &GUISession::getServer() const noexcept
{
    return _server;
}

Server &GUISession::getServer() noexcept
{
    return _server;
}

void GUISession::handleTransmission()
{
    // !todo(call protocol handler here)
}

}

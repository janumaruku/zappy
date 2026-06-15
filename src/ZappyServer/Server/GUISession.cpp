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

void GUISession::handleTransmission()
{
    // !todo(call protocol handler here)
}

}

/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AISession.hpp"

namespace zappy::server {

AISession::AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
    Server &server, Player &player): AClientSession{socket}, _server{server},
    _player{player}
{
    (void)_server;
    (void)_player;
    (void)_pending_commands;
}

void AISession::handleTransmission()
{
    // !todo(call protocol handler here)
}

} // namespace zappy::server

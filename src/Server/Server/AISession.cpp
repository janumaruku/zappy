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
}

void AISession::handleTransmission(const std::size_t &bytes)
{
    this->_transmission.append(this->_asyncReadBuffer.begin(),
        this->_asyncReadBuffer.begin() + bytes);

    if (this->_transmission.ends_with("\n")) {
        // !todo()
        this->_transmission.clear();
        return;
    }
    this->handleRead();
}

} // namespace zappy::server

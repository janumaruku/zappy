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

void GUISession::handleTransmission(const std::size_t &bytes)
{
    this->_transmission.append(this->_asyncReadBuffer.begin(),
        this->_asyncReadBuffer.begin() + bytes);

    if (this->_transmission.ends_with("\n")) {
        // !todo()
        this->_transmission.clear();
        return;
    }
    this->start();
}

}

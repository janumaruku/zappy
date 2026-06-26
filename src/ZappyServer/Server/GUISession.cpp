/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "GUISession.hpp"

#include <string>
#include <vector>

#include "Server.hpp"
#include "StringUtils.hpp"

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
    if (_transmission.empty())
        return;

    std::vector<std::string> words = utils::StringUtils::split(_transmission);

    if (words.empty()) {
        _transmission.clear();
        return;
    }

    const std::string command = words.front();
    const std::vector<std::string> args(words.begin() + 1, words.end());

    _server.handleGUICommand(*this, command, args);
    _transmission.clear();
}

}

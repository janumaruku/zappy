/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Server
*/

#include "Server.hpp"

#include <iostream>

#include "AISession.hpp"
#include "Buffer.hpp"
#include "GUISession.hpp"

namespace zappy::server {

Server::~Server() = default;

Server::Server(int port, int width, int height, std::vector<std::string> teams,
    uint playersPerTeam, uint frequency):
    _acceptor(_ioContext, network::Endpoint(port)), _teams(teams),
    _frequency(frequency), _map(width, height)
{
    for (const auto &team : _teams)
        _availableSlots[team] = playersPerTeam;
}

void Server::run()
{
    (void)_frequency;
    startAccept();
    _ioContext.run();
}

[[nodiscard]] const uint &Server::getFrequency() const
{
    return _frequency;
}


void Server::startAccept()
{
    _acceptor.asyncAccept([this](const std::error_code &error,
        const std::shared_ptr<network::ConnectedSocket> &socket) {
            if (error) {
                std::cerr << "Accept error: " << error.message() << std::endl;
                startAccept();
                return;
            }

            onAccept(socket);
        });
}

static std::string trimPacket(std::string value)
{
    while (!value.empty() && (value.back() == '\n' || value.back() == '\r' || value.back() == '\0'))
        value.pop_back();
    return value;
}

void Server::onAccept(
    const std::shared_ptr<network::ConnectedSocket> &socket)
{
    bool success = false;

    socket->write(network::buffer("WELCOME\n"),
        [&socket, &success](const std::error_code &, const std::size_t bytes) {
            if (bytes == 0) {
                std::clog << "Client disconnected!" << std::endl;
                socket->close();
            } else {
                success = true;
                std::clog << "Sent: WELCOME" << std::endl;
            }
        });

    if (!success) {
        startAccept();
        return;
    }

    std::string response(1024, '\0');
    socket->read(network::buffer(response, response.size()),
        [&socket, &response](const std::error_code &, const std::size_t &bytes) {
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                socket->close();
                response.clear();
                return;
            }
            response.resize(bytes);
        });

    response = trimPacket(response);
    std::clog << "Received handshake: " << response << std::endl;

    if (response == "GRAPHIC")
        handleGuiHandshake(socket);
    else
        handleAiHandshake(socket, response);

    startAccept();
}

std::string Server::makePlayerId()
{
    return std::to_string(_nextPlayerId++);
}

void Server::handleGuiHandshake(const std::shared_ptr<network::ConnectedSocket> &socket)
{
    _guiSessions.push_back(std::make_unique<GUISession>(socket, *this));

    auto &session = *_guiSessions.back();
    _guiProtocolHandler.handleLine("msz", session);
    _guiProtocolHandler.handleLine("tna", session);
    _guiProtocolHandler.handleLine("pnw", session);
    session.start();
}

void Server::handleAiHandshake(const std::shared_ptr<network::ConnectedSocket> &socket,
    const std::string &teamName)
{
    if (!_availableSlots.contains(teamName) || _availableSlots.at(teamName) == 0) {
        socket->write(network::buffer("0\n"), [](auto, auto) {});
        socket->close();
        return;
    }

    --_availableSlots.at(teamName);

    Player &player = _map.spawnPlayer(makePlayerId(), teamName);
    socket->write(network::buffer(std::to_string(_availableSlots.at(teamName)) + "\n"),
        [](auto, auto) {});
    socket->write(network::buffer(std::to_string(_map.getWidth()) + " "
        + std::to_string(_map.getHeight()) + "\n"), [](auto, auto) {});

    _aiSessions.push_back(std::make_unique<AISession>(socket, *this, player));
    _aiSessions.back()->start();
    notifyGUI("pnw", {player.getId()});
}

void Server::notifyGUI(const std::string &command,
    const std::vector<std::string> &args)
{
    for (auto &session : _guiSessions)
        _guiProtocolHandler.handleLine(command, *session, args);
}

void Server::broadcastToAll(const std::string &data)
{
    for (auto &a : _aiSessions) {
        if (a && !a->needsCleanup())
            a->send(data);
    }
}

void Server::forEachAISession(const std::function<void(AISession &)> &fn)
{
    for (auto &a : _aiSessions) {
        if (a && !a->needsCleanup())
            fn(*a);
    }
}

void Server::onPlayerDied(const Player &player)
{
    const auto &playerId = player.getId();

    if (!_map.removePlayer(playerId))
        return;

    notifyGUI("pdi", {playerId});

    for (auto &session : _aiSessions) {
        if (session && session->getPlayer().getId() == playerId) {
            session->markForCleanup();
            break;
        }
    }
}

}

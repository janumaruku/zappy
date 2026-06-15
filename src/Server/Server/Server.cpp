/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Server
*/

#include "include/Server.hpp"

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
    (void)playersPerTeam;
}

void Server::run()
{
    (void)_frequency;
    startAccept();
    _ioContext.run();
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

void Server::onAccept(
    const std::shared_ptr<network::ConnectedSocket> &socket)
{
    auto welcome = std::make_shared<std::string>("WELCOME\n");
    bool success = false;

    socket->write(network::buffer("WELCOME\n"),
        [&socket, &success](auto, const std::size_t bytes) {
            if (bytes == 0) {
                std::clog << "Client disconnected!" << std::endl;
                socket->close();
            } else {
                success = true;
                std::clog << "Sent: " << "WELCOME" << std::endl;
            }
        });

    if (!success)
        return;

    std::string response(1024, '\0');

    socket->read(network::buffer(response, response.size()),
        [&socket, &response](auto, const std::size_t &bytes) {
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                socket->close();
            } else {
                response.resize(bytes);
                response.pop_back();
                std::clog << "Received: " << response << std::endl;
            }
        });

    if (response == "GRAPHIC\n") {
        _guiSessions.push_back(std::make_unique<GUISession>(socket, *this));
        _guiSessions.back()->start();
    } else {

    }

    startAccept();
}

void Server::notifyGUI(const std::string &message)
{
    (void)message;
}

void Server::broadcastToAll(const std::string &data)
{
    (void)data;
}

}

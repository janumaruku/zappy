/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Server
*/

#include "Server.hpp"

#include <iostream>

#include "Buffer.hpp"

static std::string cleanLine(const std::string &line)
{
    std::string clean = line;

    while (!clean.empty() && (clean.back() == '\n' || clean.back() == '\r'))
        clean.pop_back();
    return clean;
}

static void closeSocket(const std::shared_ptr<network::ConnectedSocket> &socket)
{
    if (socket)
        socket->close();
}

namespace zappy::server {

Server::Server(int port): _acceptor(_ioContext, network::Endpoint(port))
{
}

void Server::run()
{
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

            std::cout << "Client connected from "
                << socket->remoteEndpoint().getHostname()
                << ":"
                << socket->remoteEndpoint().getPort()
                << std::endl;
            onAccept(socket);
        });
}

void Server::onAccept(
    const std::shared_ptr<network::ConnectedSocket> &socket)
{
    auto welcome = std::make_shared<std::string>("WELCOME\n");

    socket->asyncWrite(network::buffer(*welcome), [this, &socket](
        const std::error_code &err, std::size_t) {
            if (err) {
                socket->close();
                return;
            }

            auto input = std::make_shared<std::string>(4096, '\0');

            socket->asyncReadSome(network::buffer(*input, input->size()),
                [this, socket, input](const std::error_code &readError,
                std::size_t bytesRead) {
                    if (readError || bytesRead == 0) {
                        closeSocket(socket);
                        return;
                    }

                    const std::string clientName =
                        cleanLine(input->substr(0, bytesRead));

                    if (clientName == "GRAPHIC")
                        guiHandshake(socket);
                    else
                        aiHandshake(socket, clientName);
                });
        });

    startAccept();
}

void Server::aiHandshake(
    const std::shared_ptr<network::ConnectedSocket> &socket,
    const std::string &teamName)
{
    std::cout << "AI client detected for team: "
        << teamName
        << std::endl;
    auto response = std::make_shared<std::string>("AI\n");

    socket->asyncWrite(
        network::buffer(*response),
        [socket, response](const std::error_code &error, std::size_t) {
            if (error)
                closeSocket(socket);
        }
        );
}

void Server::guiHandshake(
    const std::shared_ptr<network::ConnectedSocket> &socket)
{
    std::cout << "GUI client detected" << std::endl;
    auto response = std::make_shared<std::string>("GUI\n");

    socket->asyncWrite(
        network::buffer(*response),
        [socket, response](const std::error_code &error, std::size_t) {
            if (error)
                closeSocket(socket);
        }
        );
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

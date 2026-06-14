/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Server
*/

#include <iostream>
#include <utility>

#include "Buffer.hpp"
#include "Network.hpp"

Server::Client::Client(std::shared_ptr<network::ConnectedSocket> socket)
    : socket(std::move(socket)),
      readBuffer(4096, '\0')
{}

Server::AISession::AISession(
    std::shared_ptr<Client> client,
    std::string teamName)
    : client(std::move(client)),
      teamName(std::move(teamName))
{}

Server::GUISession::GUISession(std::shared_ptr<Client> client)
    : client(std::move(client))
{}

Server::Server(int port)
    : _acceptor(_ioc, network::Endpoint(port))
{}

void Server::run()
{
    startAccept();
    _ioc.run();
}

void Server::startAccept()
{
    _acceptor.asyncAccept(
        [this](
            const std::error_code &error,
            const std::shared_ptr<network::ConnectedSocket> &socket
        ) {
            onAccept(error, socket);
        }
    );
}

void Server::onAccept(
    const std::error_code &error,
    const std::shared_ptr<network::ConnectedSocket> &socket)
{
    if (error) {
        std::cerr << "Accept error: " << error.message() << std::endl;
        startAccept();
        return;
    }

    auto client = std::make_shared<Client>(socket);
    _pendingClients.push_back(client);

    std::cout << "Client connected from "
              << socket->remoteEndpoint().getHostname()
              << ":"
              << socket->remoteEndpoint().getPort()
              << std::endl;

    client->writeBuffer = "WELCOME\n";

    client->socket->asyncWrite(
        network::buffer(client->writeBuffer),
        [this, client](const std::error_code &writeError, std::size_t) {
            if (writeError) {
                removeClient(client);
                return;
            }

            startHandshakeRead(client);
        }
    );

    startAccept();
}

void Server::startHandshakeRead(const std::shared_ptr<Client> &client)
{
    client->readBuffer.assign(4096, '\0');

    client->socket->asyncReadSome(
        network::buffer(client->readBuffer, client->readBuffer.size()),
        [this, client](const std::error_code &error, std::size_t bytesRead) {
            onHandshakeRead(client, error, bytesRead);
        }
    );
}

void Server::onHandshakeRead(
    const std::shared_ptr<Client> &client,
    const std::error_code &error,
    std::size_t bytesRead)
{
    if (error || bytesRead == 0) {
        removeClient(client);
        return;
    }

    const std::string clientName =
        cleanLine(client->readBuffer.substr(0, bytesRead));

    std::cout << "Handshake received: " << clientName << std::endl;

    if (clientName == "GRAPHIC") {
        guiHandshake(client);
        return;
    }

    aiHandshake(client, clientName);
}

void Server::aiHandshake(
    const std::shared_ptr<Client> &client,
    const std::string &teamName)
{
    client->type = ClientType::AI;

    auto session = std::make_shared<AISession>(client, teamName);
    _aiSessions.push_back(session);
    _pendingClients.remove(client);

    std::cout << "AI session created for team: "
              << teamName
              << std::endl;
    client->writeBuffer = "AI\n";

    client->socket->asyncWrite(
        network::buffer(client->writeBuffer),
        [this, client](const std::error_code &writeError, std::size_t) {
            if (writeError) {
                removeClient(client);
                return;
            }

            startRead(client);
        }
    );
}

void Server::guiHandshake(const std::shared_ptr<Client> &client)
{
    client->type = ClientType::GUI;

    auto session = std::make_shared<GUISession>(client);
    _guiSessions.push_back(session);
    _pendingClients.remove(client);

    std::cout << "GUI session created" << std::endl;
    client->writeBuffer = "GUI\n";

    client->socket->asyncWrite(
        network::buffer(client->writeBuffer),
        [this, client](const std::error_code &writeError, std::size_t) {
            if (writeError) {
                removeClient(client);
                return;
            }

            startRead(client);
        }
    );
}

void Server::startRead(const std::shared_ptr<Client> &client)
{
    client->readBuffer.assign(4096, '\0');

    client->socket->asyncReadSome(
        network::buffer(client->readBuffer, client->readBuffer.size()),
        [this, client](const std::error_code &error, std::size_t bytesRead) {
            onRead(client, error, bytesRead);
        }
    );
}

void Server::onRead(
    const std::shared_ptr<Client> &client,
    const std::error_code &error,
    std::size_t bytesRead)
{
    if (error || bytesRead == 0) {
        removeClient(client);
        return;
    }

    const std::string message =
        cleanLine(client->readBuffer.substr(0, bytesRead));

    if (client->type == ClientType::GUI)
        std::cout << "GUI command: " << message << std::endl;
    else if (client->type == ClientType::AI)
        std::cout << "AI command: " << message << std::endl;
    else
        std::cout << "Unknown client command: " << message << std::endl;

    startRead(client);
}

void Server::removeClient(const std::shared_ptr<Client> &client)
{
    client->socket->close();

    _pendingClients.remove(client);

    _aiSessions.remove_if(
        [&client](const std::shared_ptr<AISession> &session) {
            return session->client == client;
        }
    );

    _guiSessions.remove_if(
        [&client](const std::shared_ptr<GUISession> &session) {
            return session->client == client;
        }
    );

    std::cout << "Client disconnected" << std::endl;
}

void Server::notifyGUI(const std::string &message)
{
    for (const auto &session : _guiSessions) {
        session->client->writeBuffer = message;

        session->client->socket->asyncWrite(
            network::buffer(session->client->writeBuffer),
            [](const std::error_code &error, std::size_t) {
                if (error)
                    std::cerr << "GUI write error: "
                              << error.message()
                              << std::endl;
            }
        );
    }
}

void Server::broadcastToAll(const std::string &data)
{
    for (const auto &session : _aiSessions) {
        session->client->writeBuffer = data;

        session->client->socket->asyncWrite(
            network::buffer(session->client->writeBuffer),
            [](const std::error_code &error, std::size_t) {
                if (error)
                    std::cerr << "Broadcast write error: "
                              << error.message()
                              << std::endl;
            }
        );
    }

    for (const auto &session : _guiSessions) {
        session->client->writeBuffer = data;

        session->client->socket->asyncWrite(
            network::buffer(session->client->writeBuffer),
            [](const std::error_code &error, std::size_t) {
                if (error)
                    std::cerr << "Broadcast write error: "
                              << error.message()
                              << std::endl;
            }
        );
    }
}

std::string Server::cleanLine(const std::string &line)
{
    std::string clean = line;

    while (!clean.empty() && (clean.back() == '\n' || clean.back() == '\r'))
        clean.pop_back();

    return clean;
}
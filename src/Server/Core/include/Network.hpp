/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Server
*/

#pragma once

#include <list>
#include <memory>
#include <string>
#include <system_error>

#include "Acceptor.hpp"
#include "ConnectedSocket.hpp"
#include "Endpoint.hpp"
#include "IoContext.hpp"

class Server {
public:
    explicit Server(int port);

    void run();

private:
    enum class ClientType {
        UNKNOWN,
        AI,
        GUI
    };

    struct Client {
        explicit Client(std::shared_ptr<network::ConnectedSocket> socket);

        std::shared_ptr<network::ConnectedSocket> socket;
        std::string readBuffer;
        std::string writeBuffer;
        ClientType type = ClientType::UNKNOWN;
    };

    struct AISession {
        AISession(std::shared_ptr<Client> client, std::string teamName);

        std::shared_ptr<Client> client;
        std::string teamName;
    };

    struct GUISession {
        explicit GUISession(std::shared_ptr<Client> client);

        std::shared_ptr<Client> client;
    };

    network::IOContext _ioc;
    network::Acceptor _acceptor;

    std::list<std::shared_ptr<Client>> _pendingClients;
    std::list<std::shared_ptr<AISession>> _aiSessions;
    std::list<std::shared_ptr<GUISession>> _guiSessions;

    void startAccept();

    void onAccept(
        const std::error_code &error,
        const std::shared_ptr<network::ConnectedSocket> &socket
    );

    void startHandshakeRead(const std::shared_ptr<Client> &client);

    void onHandshakeRead(
        const std::shared_ptr<Client> &client,
        const std::error_code &error,
        std::size_t bytesRead
    );

    void aiHandshake(
        const std::shared_ptr<Client> &client,
        const std::string &teamName
    );

    void guiHandshake(const std::shared_ptr<Client> &client);

    void startRead(const std::shared_ptr<Client> &client);

    void onRead(
        const std::shared_ptr<Client> &client,
        const std::error_code &error,
        std::size_t bytesRead
    );

    void removeClient(const std::shared_ptr<Client> &client);

    void notifyGUI(const std::string &message);
    void broadcastToAll(const std::string &data);

    static std::string cleanLine(const std::string &line);
};
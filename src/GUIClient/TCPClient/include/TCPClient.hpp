/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** TCPClient.hpp
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_
#include <string>

#include "ConnectedSocket.hpp"

namespace zappy::gui {
class TCPClient {
public:
    TCPClient() = delete;

    explicit TCPClient(network::IOContext &ioc, int port,
        const std::string &hostname);

    void start();

    void send(std::string data) const;

    std::string receive();

    void pollAll() const;

private:
    network::IOContext &_ioc;
    network::ConnectedSocket _socket;
    std::string _readBuffer;
    std::string _readAsyncBuffer;
    std::string _transmission;

    // ProtocolHandler _protocol;
    void handleTransmission(const size_t &bytes);

    void startRead();
};
}

#endif

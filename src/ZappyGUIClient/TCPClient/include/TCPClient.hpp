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
#include "ProtocolHandler.hpp"

namespace zappy::gui {
class TCPClient {
public:
    TCPClient() = delete;

    explicit TCPClient(network::IOContext &ioc, int port,
        const std::string &hostname, WorldState &worldState);

    void start();

    void send(std::string data);

    std::string receive();

    void pollAll() const;
    bool isTransmissionReady(const std::size_t &bytes, const std::string& buffer);

private:
    network::IOContext &_ioc;
    network::ConnectedSocket _socket;
    std::string _readBuffer;
    std::string _asyncReadBuffer;
    std::string _transmission;
    std::string _transmissionTemp;
    utils::Logger _logger{"TCP-CLIENT", LogLevel::INFO, true};
    ProtocolHandler _protocol;

    void handleTransmission();

    void startRead();
};
}

#endif

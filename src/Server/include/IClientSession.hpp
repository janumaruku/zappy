/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef ICLIENTSESSION_HPP_
    #define ICLIENTSESSION_HPP_

#include <queue>
#include <string>
#include "ConnectedSocket.hpp"

namespace zappy::server {

class IClientSession {
public:
    IClientSession() = delete;
    virtual ~IClientSession() = default;

    virtual void start() = 0;
    virtual void send(std::string &data) = 0;
    virtual std::string receive() = 0;

protected:
    network::ConnectedSocket _socket;
    std::string _readBuffer;
    std::string _readAsyncBuffer;
    std::string _transmission;
    std::queue<std::string> _writeQueue;

    virtual void handleRead() = 0;
    virtual void handleWrite() = 0;
    virtual void handleTransmission() = 0;
};

}

#endif

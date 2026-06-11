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
    virtual ~IClientSession() = 0;

    virtual void start() = 0;
    virtual void send(std::string &data) = 0;
    virtual void receive() = 0;

protected:
    network::ConnectedSocket _socket;
    std::string _read_buffer;
    std::queue<std::string> _write_queue;

    virtual void handleRead() = 0;
    virtual void handleWrite() = 0;
    virtual void handleTransmission() = 0;
};

}

#endif

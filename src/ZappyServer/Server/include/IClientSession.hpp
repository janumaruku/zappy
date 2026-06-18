/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef ICLIENTSESSION_HPP_
    #define ICLIENTSESSION_HPP_

#include <cstddef>
#include <queue>
#include <string>
#include "ConnectedSocket.hpp"

namespace zappy::server {

class IClientSession {
public:
    virtual ~IClientSession() = default;

    virtual void start() = 0;
    virtual void send(const std::string &data) = 0;
    virtual std::string receive() = 0;

protected:
    virtual void handleRead() = 0;
    virtual void handleWrite(const std::string& message) = 0;
    virtual void handleTransmission() = 0;
};

}

#endif

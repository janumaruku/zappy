/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#ifndef MYFTP_SOCKET_HPP
#define MYFTP_SOCKET_HPP

#include "Endpoint.hpp"
#include "Logger.hpp"

namespace network {
class IOContext;

class ListeningSocket {
public:
    explicit ListeningSocket(IOContext &ioContext);

    explicit ListeningSocket(IOContext &ioContext, const int &socketFd);

    [[nodiscard]] int getFd() const noexcept;

    [[nodiscard]] const Endpoint &remoteEndpoint() const noexcept;

private:
    int _socketFd = -1;
    Endpoint _endpoint;
    // utils::Logger _logger{"LISTENING-SOCKET", ULogLevel::INFO, true};
};
} // ftp

#endif //MYFTP_SOCKET_HPP

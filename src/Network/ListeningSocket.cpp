/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#include "ListeningSocket.hpp"

#include <stdexcept>
#include <sys/socket.h>

#include "IoContext.hpp"

namespace network {
ListeningSocket::ListeningSocket(IOContext &/*ioContext*/): _socketFd{
    socket(AF_INET, SOCK_STREAM, 0)}
{
    if (_socketFd == -1)
        throw std::runtime_error("Socket creation failed");
}

ListeningSocket::ListeningSocket(IOContext &/*ioContext*/,
    const int &socketFd): _socketFd{socketFd}
{}

int ListeningSocket::getFd() const noexcept
{
    return _socketFd;
}

const Endpoint &ListeningSocket::remoteEndpoint() const noexcept
{
    return _endpoint;
}
} // ftp

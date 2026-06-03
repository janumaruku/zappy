/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ConnectedSocket
*/

#include "ConnectedSocket.hpp"

#include <stdexcept>
#include <unistd.h>

#include "ErrorCode.hpp"
#include "IoContext.hpp"

namespace network {
ConnectedSocket::ConnectedSocket(IOContext &ioContext):
    _socketFd{socket(AF_INET, SOCK_STREAM, 0)}, _ioContext{ioContext}
{
    if (_socketFd == -1)
        throw std::runtime_error("Socket creation failed");

    _ioContext.registerFileDescriptor(_socketFd);
}

ConnectedSocket::ConnectedSocket(
    IOContext &ioContext, const int &clientFd, Endpoint &&endpoint):
    _socketFd{clientFd}, _endpoint{std::move(endpoint)}, _ioContext{ioContext}
{
    _ioContext.registerFileDescriptor(_socketFd);
}

void ConnectedSocket::connect(Endpoint &endpoint)
{
    _endpoint = endpoint;
    if (::connect(_socketFd,
        reinterpret_cast<sockaddr *>(&endpoint.getAddress()),
        sizeof(endpoint.getAddress())) == -1)
        throw std::runtime_error{"Connect failed"};
}

int ConnectedSocket::getFd() const noexcept
{
    return _socketFd;
}

const Endpoint &ConnectedSocket::remoteEndpoint() const noexcept
{
    return _endpoint;
}

void ConnectedSocket::close() const
{
    ::close(_socketFd);
    _ioContext.unregisterFileDescriptor(_socketFd);
}

void ConnectedSocket::write(
    const ConstBuffer &buffer, const Callback &handler) const
{
    auto result = ::write(_socketFd, buffer.data, buffer.size);

    if (result == -1)
        handler(FtpErrorCode::CS_WRITE_ERROR, 0);
    else
        handler(std::error_code{}, result);
}

void ConnectedSocket::read(MutableBuffer buffer,
    const Callback &handler) const
{
    const ssize_t result = ::read(_socketFd, buffer.data, buffer.size);

    if (result == -1)
        handler(FtpErrorCode::CS_READ_ERROR, 0);
    else
        handler(std::error_code{}, result);
}

void ConnectedSocket::asyncReadSome(
    MutableBuffer outputBuffer, const Callback &handler) const
{
    _ioContext.postRead(_socketFd, [this, outputBuffer, handler] {
        const ssize_t result =
            ::read(_socketFd, outputBuffer.data, outputBuffer.size);

        if (result == -1)
            handler(FtpErrorCode::CS_READ_ERROR, 0);
        else
            handler(std::error_code{}, result);
    });
}

void ConnectedSocket::asyncWrite(
    const ConstBuffer &buffer, const Callback &handler) const
{
    _ioContext.postWrite(_socketFd, [this, buffer, handler] {
        const ssize_t result = ::write(_socketFd, buffer.data, buffer.size);

        if (result == -1)
            handler(FtpErrorCode::CS_WRITE_ERROR, 0);
        else
            handler(std::error_code{}, result);
    });
}

IOContext &ConnectedSocket::getIOContext() const noexcept
{
    return _ioContext;
}
} // namespace network

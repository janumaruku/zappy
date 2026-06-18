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
ConnectedSocket::ConnectedSocket(IOContext &ioContext,
    utils::LoggerConfig config):
    _socketFd{socket(AF_INET, SOCK_STREAM, 0)}, _ioContext{ioContext}
{
    config.context = "TCP-CLIENT";
    _logger.config(config);
    if (_socketFd == -1)
        throw std::runtime_error("Socket creation failed");

    _ioContext.registerFileDescriptor(_socketFd);
}

ConnectedSocket::ConnectedSocket(IOContext &ioContext, const int &clientFd,
    Endpoint &&endpoint, utils::LoggerConfig config):
    _socketFd{clientFd}, _endpoint{std::move(endpoint)}, _ioContext{ioContext}
{
    _logger.config(config);
    _ioContext.registerFileDescriptor(_socketFd);
}

void ConnectedSocket::connect(const Endpoint &endpoint)
{
    _endpoint = endpoint;
    if (::connect(_socketFd,
        reinterpret_cast<const sockaddr *>(&endpoint.getAddress()),
        sizeof(endpoint.getAddress())) == -1)
        throw std::runtime_error{"Connect failed"};

    std::stringstream host;
    host << endpoint.getHostname() << ":" << endpoint.getPort();
    _logger.start(LogLevel::INFO) << "Connected to remote endpoint: "
        << host.str() << utils::END;
}

int ConnectedSocket::getFd() const noexcept
{
    return _socketFd;
}

const Endpoint &ConnectedSocket::remoteEndpoint() const noexcept
{
    return _endpoint;
}

void ConnectedSocket::close()
{
    _logger.start(LogLevel::INFO) << "Client disconnected!" << utils::END;
    ::close(_socketFd);
    _ioContext.unregisterFileDescriptor(_socketFd);
}

void ConnectedSocket::write(
    const ConstBuffer &buffer, const Callback &handler)
{
    auto result = ::write(_socketFd, buffer.data, buffer.size);

    if (result == -1) {
        handler(FtpErrorCode::CS_WRITE_ERROR, 0);
    } else {
        _logger.start(LogLevel::DEBUG_LEVEL) << "Sent: " << result
            << " bytes" << utils::END;
        handler(std::error_code{}, result);
    }
}

void ConnectedSocket::read(MutableBuffer buffer,
    const Callback &handler)
{
    const ssize_t result = ::read(_socketFd, buffer.data, buffer.size);

    if (result == -1) {
        handler(FtpErrorCode::CS_READ_ERROR, 0);
    } else {
        _logger.start(LogLevel::DEBUG_LEVEL) << "Received: " << result
            << " bytes" << utils::END;
        handler(std::error_code{}, result);
    }
}

void ConnectedSocket::asyncReadSome(
    MutableBuffer outputBuffer, const Callback &handler)
{
    _ioContext.postRead(_socketFd, [this, outputBuffer, handler] {
        const ssize_t result =
            ::read(_socketFd, outputBuffer.data, outputBuffer.size);

        if (result == -1) {
            handler(FtpErrorCode::CS_READ_ERROR, 0);
        } else {
            _logger.start(LogLevel::DEBUG_LEVEL) << "Received: " << result
                << " bytes" << utils::END;
            handler(std::error_code{}, result);
        }
    });
}

void ConnectedSocket::asyncWrite(
    const ConstBuffer &buffer, const Callback &handler)
{
    _ioContext.postWrite(_socketFd, [this, buffer, handler] {
        const ssize_t result = ::write(_socketFd, buffer.data, buffer.size);

        if (result == -1) {
            handler(FtpErrorCode::CS_WRITE_ERROR, 0);
        } else {
            _logger.start(LogLevel::DEBUG_LEVEL) << "Sent: " << result
                << " bytes" << utils::END;
            handler(std::error_code{}, result);
        }
    });
}

IOContext &ConnectedSocket::getIOContext() const noexcept
{
    return _ioContext;
}
} // namespace network

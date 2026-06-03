/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ConnectedSocket
*/

#ifndef MYFTP_CONNECTEDSOCKET_HPP
#define MYFTP_CONNECTEDSOCKET_HPP

#include <functional>
#include <queue>

#include "Buffer.hpp"
#include "Endpoint.hpp"
#include "Logger.hpp"

namespace network {
class IOContext;

class ConnectedSocket {
public:
    using Callback = std::function<void(const std::error_code &,
        const std::size_t &)>;
    using PendingOperation = std::function<void()>;

    explicit ConnectedSocket(IOContext &ioContext);

    explicit ConnectedSocket(IOContext &ioContext, const int &clientFd,
        Endpoint &&endpoint);

    void connect(Endpoint &endpoint);

    [[nodiscard]] int getFd() const noexcept;

    [[nodiscard]] const Endpoint &remoteEndpoint() const noexcept;

    void close() const;

    void write(const ConstBuffer &buffer, const Callback &handler) const;

    void read(MutableBuffer buffer, const Callback &handler) const;

    void asyncReadSome(MutableBuffer outputBuffer,
        const Callback &handler) const;

    void asyncWrite(const ConstBuffer &buffer, const Callback &handler) const;

    [[nodiscard]] IOContext &getIOContext() const noexcept;

private:
    int _socketFd = -1;
    Endpoint _endpoint;
    IOContext &_ioContext;
    std::queue<PendingOperation> _handlers;
    // utils::Logger _logger{"CONNECTED-SOCKET", ULogLevel::INFO, true};
};
}

#endif //MYFTP_CONNECTEDSOCKET_HPP

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

/**
 * @class ConnectedSocket
 * @brief Represents an open TCP connection, either accepted server-side or connected client-side.
 *
 * This is the main handle for sending and receiving data. It supports both synchronous
 * operations (@ref read, @ref write) and asynchronous ones (@ref asyncReadSome, @ref asyncWrite).
 * Async operations register a callback with the @ref IOContext and return immediately.
 * The callback is invoked when the @ref IOContext is running and the socket is ready.
 *
 * On the server side, instances are produced by @ref Acceptor::asyncAccept.
 * On the client side, use the single-argument constructor followed by @ref connect.
 */
class ConnectedSocket {
public:
    /// @brief Callback type invoked when an operation completes, with an error code and byte count.
    using Callback = std::function<void(const std::error_code &,
        const std::size_t &)>;

    /// @brief Internal type for queued async operations. Not intended for direct use.
    using PendingOperation = std::function<void()>;

    /**
     * @brief Constructs a client-side socket. Call @ref connect to establish a connection.
     * @param ioContext The event loop that will drive async operations on this socket.
     */
    explicit ConnectedSocket(IOContext &ioContext);

    /**
     * @brief Constructs a server-side socket from an already-accepted file descriptor.
     * @param ioContext The event loop that will drive async operations on this socket.
     * @param clientFd  The file descriptor returned by @c accept().
     * @param endpoint  The remote @ref Endpoint of the connected client.
     */
    explicit ConnectedSocket(IOContext &ioContext, const int &clientFd,
        Endpoint &&endpoint);

    /**
     * @brief Connects this socket to a remote @ref Endpoint (client-side use).
     * @param endpoint The address and port to connect to.
     */
    void connect(Endpoint &endpoint);

    /// @brief Returns the file descriptor of this socket.
    [[nodiscard]] int getFd() const noexcept;

    /// @brief Returns the @ref Endpoint of the remote peer.
    [[nodiscard]] const Endpoint &remoteEndpoint() const noexcept;

    /// @brief Closes the socket.
    void close() const;

    /**
     * @brief Sends data synchronously. Blocks until all bytes are written or an error occurs.
     * @param buffer  Data to send. See @ref ConstBuffer.
     * @param handler Called with the result when the write completes.
     */
    void write(const ConstBuffer &buffer, const Callback &handler) const;

    /**
     * @brief Receives data synchronously. Blocks until data is available or an error occurs.
     * @param buffer  Destination buffer. See @ref MutableBuffer.
     * @param handler Called with the result when the read completes.
     */
    void read(MutableBuffer buffer, const Callback &handler) const;

    /**
     * @brief Schedules an async read. Returns immediately and calls @p handler when data arrives.
     *
     * The callback receives the number of bytes read. Pay attention to the lifetime of
     * @p outputBuffer. See the warning in @ref async_model.
     *
     * @param outputBuffer Destination buffer. See @ref MutableBuffer.
     * @param handler      Called with @c (error_code, bytes_read) when data is available.
     */
    void asyncReadSome(MutableBuffer outputBuffer,
        const Callback &handler) const;

    /**
     * @brief Schedules an async write. Returns immediately and calls @p handler when done.
     *
     * Pay attention to the lifetime of @p buffer. See the warning in @ref async_model.
     *
     * @param buffer  Data to send. See @ref ConstBuffer.
     * @param handler Called with @c (error_code, bytes_written) when the write completes.
     */
    void asyncWrite(const ConstBuffer &buffer, const Callback &handler) const;

    /// @brief Returns the @ref IOContext this socket is registered with.
    [[nodiscard]] IOContext &getIOContext() const noexcept;

private:
    int _socketFd = -1;                    ///< File descriptor of this socket.
    Endpoint _endpoint;                    ///< Remote peer address and port.
    IOContext &_ioContext;                 ///< Event loop driving async operations.
    std::queue<PendingOperation> _handlers; ///< Queue of pending async operations.
    // utils::Logger _logger{"CONNECTED-SOCKET", ULogLevel::INFO, true};
};
}

#endif //MYFTP_CONNECTEDSOCKET_HPP

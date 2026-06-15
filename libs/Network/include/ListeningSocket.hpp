/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Socket
*/

#ifndef ZAPPY_SOCKET_HPP
#define ZAPPY_SOCKET_HPP

#include "Endpoint.hpp"
#include "Logger.hpp"

namespace network {
class IOContext;

/**
 * @class ListeningSocket
 * @brief A passive TCP socket that waits for incoming connections.
 *
 * This class is an internal detail of @ref Acceptor. You do not need to use it directly.
 * It wraps the @c socket(), @c bind(), and @c listen() calls and registers the file
 * descriptor with the @ref IOContext so the @ref Acceptor can be notified when a
 * connection is ready to be accepted.
 */
class ListeningSocket {
public:
    /**
     * @brief Creates a new listening socket and registers it with @p ioContext.
     * @param ioContext The event loop that will watch this socket.
     */
    explicit ListeningSocket(IOContext &ioContext);

    /**
     * @brief Wraps an already-open socket file descriptor.
     * @param ioContext The event loop that will watch this socket.
     * @param socketFd  An existing socket file descriptor.
     */
    explicit ListeningSocket(IOContext &ioContext, const int &socketFd);

    /// @brief Returns the file descriptor of the listening socket.
    [[nodiscard]] int getFd() const noexcept;

    /// @brief Returns the local @ref Endpoint this socket is bound to.
    [[nodiscard]] const Endpoint &remoteEndpoint() const noexcept;

private:
    int _socketFd = -1;    ///< File descriptor of the listening socket.
    Endpoint _endpoint;    ///< Local address and port this socket is bound to.
    // utils::Logger _logger{"LISTENING-SOCKET", ULogLevel::INFO, true};
};
} // ftp

#endif //ZAPPY_SOCKET_HPP

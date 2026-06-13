/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#ifndef ZAPPY_ACCEPTOR_HPP
#define ZAPPY_ACCEPTOR_HPP

#include <functional>
#include <memory>
#include <queue>
#include <system_error>

#include "ConnectedSocket.hpp"
#include "Endpoint.hpp"
#include "ErrorCode.hpp"
#include "ListeningSocket.hpp"
#include "Logger.hpp"

namespace network {
/**
 * @class Acceptor
 * @brief Accepts incoming TCP connections asynchronously.
 *
 * `Acceptor` binds and listens on a given @ref Endpoint, then accepts incoming
 * connections one at a time via @ref asyncAccept. Each accepted connection is
 * handed to your callback as a @ref ConnectedSocket.
 *
 * It relies on an @ref IOContext to know when the listening socket is ready to
 * accept. No connection is accepted until the context is running.
 *
 * Typical usage:
 * @code
 * network::IOContext ioContext;
 * network::Acceptor acceptor(ioContext, network::Endpoint{8080});
 * acceptor.asyncAccept([&](const std::error_code &ec,
 *     const std::shared_ptr<network::ConnectedSocket> &socket) {
 *     if (!ec)
 *         startClient(socket);
 *     acceptor.asyncAccept(...); // re-arm
 * });
 * ioContext.run();
 * @endcode
 */
class Acceptor {
public:
    /// @brief Callback type invoked when a connection is accepted or an error occurs.
    using ConnectionHandler = std::function<void(const std::error_code &,
        const std::shared_ptr<ConnectedSocket> &)>;

    /**
     * @brief Constructs an Acceptor, binds to @p endpoint, and starts listening.
     *
     * @param ioContext The event loop that will drive async operations.
     * @param endpoint  The local address and port to listen on.
     *
     * @throw std::runtime_error when the bind call or listen call fails.
     */
    explicit Acceptor(IOContext &ioContext, Endpoint &&endpoint);

    /**
     * @brief Returns the file descriptor of the underlying listening socket.
     */
    [[nodiscard]] int getSocketFd() const noexcept;

    /**
     * @brief Registers a callback to be called when a new connection is accepted.
     *
     * The callback receives a `std::error_code` (see `FtpErrorCode`
     * for possible values) and a @ref ConnectedSocket. The `std::error_code`
     * is set when something unexpected happens (`accept()` fails) and the
     * ConnectedSocket pointer is `nullptr`.
     *
     * It is called once. Call @ref asyncAccept again inside the callback to keep
     * accepting new connections.
     *
     * @param handler Callback invoked with `(error_code, shared_ptr<ConnectedSocket>)`.
     */
    void asyncAccept(const ConnectionHandler &handler);

private:
    Endpoint _endpoint; ///< Local address and port the acceptor is bound to.
    ListeningSocket _socket; ///< Underlying passive socket that listens for connections.
    std::queue<ConnectionHandler> _handlerFunction; ///< Queue of pending accept callbacks.
    utils::Logger _logger{"ACCEPTOR", ULogLevel::INFO, true}; ///< Logger for accept events.
    IOContext &_ioContext; ///< Event loop that drives async accept operations.

    static FtpErrorCode getAcceptorErrorCode(const int &error);

    [[nodiscard]] std::shared_ptr<ConnectedSocket> acceptClient() const;
};
} // ftp

#endif //ZAPPY_ACCEPTOR_HPP

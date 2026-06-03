/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Acceptor
*/

#ifndef MYFTP_ACCEPTOR_HPP
#define MYFTP_ACCEPTOR_HPP

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
class Acceptor {
public:
    using ConnectionHandler = std::function<void(const std::error_code &,
        const std::shared_ptr<ConnectedSocket> &)>;

    explicit Acceptor(IOContext &ioContext, Endpoint &&endpoint);

    [[nodiscard]] int getSocketFd() const noexcept;

    void asyncAccept(const ConnectionHandler &handler);

private:
    Endpoint _endpoint;
    ListeningSocket _socket;
    std::queue<ConnectionHandler> _handlerFunction;
    utils::Logger _logger{"ACCEPTOR", ULogLevel::INFO, true};
    IOContext &_ioContext;

    static FtpErrorCode getAcceptorErrorCode(const int &error);

    [[nodiscard]] std::shared_ptr<ConnectedSocket> acceptClient() const;
};
} // ftp

#endif //MYFTP_ACCEPTOR_HPP

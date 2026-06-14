/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AClientSession.hpp"

namespace zappy::server {

static constexpr std::size_t READ_BUFFER_SIZE = 4096;

AClientSession::AClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket): IClientSession{},
    _socket{socket}
{
    this->_readBuffer.resize(READ_BUFFER_SIZE);
    this->_asyncReadBuffer.resize(READ_BUFFER_SIZE);
}

void AClientSession::start()
{
    handleRead();
}

void AClientSession::send(std::string &data)
{
    _socket->write(network::buffer(data),
        [this, &data](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                return;
            }

            if (bytes == 0) {
                std::clog << "Client disconnected!" << std::endl;
                this->_socket->close();
                return;
            }

            std::clog << "Send: " << data << std::endl;
        });
}

std::string AClientSession::receive()
{
    _socket->read(network::buffer(this->_readBuffer, this->_readBuffer.size()),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                return;
            }

            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                _socket->close();
                return;
            }

            std::clog << "Received: " << _readBuffer << std::endl;
        });

    return std::string{_readBuffer.data(), _readBuffer.size()};
}

void AClientSession::handleRead()
{
    _socket->asyncReadSome(network::buffer(_asyncReadBuffer, READ_BUFFER_SIZE),
        [this](const std::error_code &ec, const std::size_t &bytes) {
            if (ec) {
                std::cerr << ec.message() << std::endl;
                return;
            }

            if (bytes == 0) {
                std::clog << "Client disconnected!" << std::endl;
                _socket->close();
                return;
            }

            handleTransmission(bytes);
        });
}

void AClientSession::handleWrite(const std::string &message)
{
    _socket->asyncWrite(network::buffer(message),
        [this, &message](const std::error_code &ec, const std::size_t &bytes) {
            if (ec) {
                std::cerr << ec.message() << std::endl;
                return;
            }

            if (bytes == 0) {
                std::clog << "Client disconnected!" << std::endl;
                _socket->close();
                return;
            }

            std::clog << "Sent: " << message << std::endl;
            handleRead();
        });
}
}

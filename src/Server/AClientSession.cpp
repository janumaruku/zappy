/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AClientSession.hpp"

namespace zappy::server {

static constexpr std::size_t READ_BUFFER_SIZE = 4096;

AClientSession::AClientSession()
{
    this->_readBuffer.resize(READ_BUFFER_SIZE);
}

void AClientSession::start()
{
    _socket.asyncReadSome(network::buffer(_readBuffer, READ_BUFFER_SIZE),
        [this](const std::error_code &ec, const std::size_t &bytes) {
            if (ec) {
                _socket.close();
                return;
            }

            if (bytes == 0) {
                _socket.close();
                return;
            }

            handleRead();
            start();
        });
}

void AClientSession::send(std::string &data)
{
    this->_socket.write(network::buffer(data),
        [this, &data](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                this->_socket.close();
            }
            std::clog << "Send: " << data << std::endl;
        });
}

std::string AClientSession::receive()
{
    this->_socket.read(network::buffer(this->_readBuffer,
                           this->_readBuffer.size()),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                _socket.close();
            }
            std::clog << "Received: " << this->_readBuffer << std::endl;
        });
    return this->_readBuffer;
}

void AClientSession::handleRead()
{
    if (!_readBuffer.empty())
        receive();
}

void AClientSession::handleWrite()
{
    if (_writeQueue.empty())
        return;

    const std::string &out = _writeQueue.front();

    _socket.asyncWrite(network::buffer(out),
        [this](const std::error_code &ec, const std::size_t &bytes) {
            if (ec) {
                _socket.close();
                return;
            }

            if (_writeQueue.empty())
                return;

            if (bytes < _writeQueue.front().size()) {
                _writeQueue.front().erase(0, bytes);
                handleWrite();
            } else {
                _writeQueue.pop();
                if (!_writeQueue.empty())
                    handleWrite();
            }
        });
}

}

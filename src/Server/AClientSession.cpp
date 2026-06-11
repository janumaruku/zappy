/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AClientSession.hpp"

namespace zappy::server {

static constexpr std::size_t READ_BUFFER_SIZE = 4096;

AClientSession::AClientSession() {
    this->_read_buffer.resize(READ_BUFFER_SIZE);
}

void AClientSession::start()
{
    _socket.asyncReadSome(network::buffer(_read_buffer, READ_BUFFER_SIZE),
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

// Maybe put datatype to std::string
void AClientSession::receive() {
    this->_socket.read(network::buffer(
        this->_read_buffer,
        this->_read_buffer.size()),
    [this](const std::error_code &err, const std::size_t &bytes) {
        if (err) {
            std::cerr << err.message() << std::endl;
        }
        if (bytes == 0) {
            std::clog << "Client disconnected" << std::endl;
            _socket.close();
        }
        std::clog << "Received: " << this->_read_buffer << std::endl;
    });
    // return this->_read_buffer;
}

void AClientSession::handleRead()
{
    if (!_read_buffer.empty())
        receive();
}

void AClientSession::handleWrite()
{
    if (_write_queue.empty())
        return;

    const std::string &out = _write_queue.front();

    _socket.asyncWrite(network::buffer(out), [this](const std::error_code &ec,
        const std::size_t &bytes) {
        if (ec) {
            _socket.close();
            return;
        }

        if (_write_queue.empty())
            return;

        if (bytes < _write_queue.front().size()) {
            _write_queue.front().erase(0, bytes);
            handleWrite();
        } else {
            _write_queue.pop();
            if (!_write_queue.empty())
                handleWrite();
        }
    });
}

}

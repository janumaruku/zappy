/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AClientSession.hpp"

namespace zappy::server {

static constexpr std::size_t READ_BUFFER_SIZE = 4096;

void AClientSession::start()
{
    _read_buffer.resize(READ_BUFFER_SIZE);
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

            _read_buffer.resize(bytes);

            handleRead();

            start();
        });
}

void AClientSession::send(std::string &data)
{
    const bool writeInProgress = !_write_queue.empty();
    _write_queue.emplace(data);

    if (!writeInProgress)
        handleWrite();
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

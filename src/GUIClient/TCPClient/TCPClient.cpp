/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** TCPClient.cpp
*/

#include "TCPClient.hpp"

#include "IoContext.hpp"

namespace zappy::gui {
TCPClient::TCPClient(network::IOContext &ioc, const int port,
    const std::string &hostname): _ioc(ioc), _socket(_ioc)
{
    try {
        network::Endpoint endpoint(port, hostname);
        _socket.connect(endpoint);
        if (receive() == "WELCOME") {
            send("GRAPHIC");
        } else {
            throw;
        }
    } catch (std::exception &) {
        throw;
    }
}

void TCPClient::start()
{
    startRead();
}

void TCPClient::send(std::string data) const
{
    _socket.write(network::buffer(data),
        [this, &data](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                _socket.close();
            }
            std::clog << "Send: " << data << std::endl;
        });
}

std::string TCPClient::receive()
{
    _socket.read(network::buffer(_readBuffer, _readBuffer.size()),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                _socket.close();
            }
            std::clog << "Received: " << _readBuffer << std::endl;
        });
    return _readBuffer;
}

void TCPClient::pollAll() const
{
    _ioc.pollAll();
}

void TCPClient::handleRead(const size_t &bytes)
{
    _transmission.append(_readBuffer.begin(), _readBuffer.begin() + bytes);

    if (_transmission.ends_with("\n")) {
        // call protocol
        _transmission.clear();
        return;
    }
    handleRead(bytes);
}

void TCPClient::startRead()
{
    _socket.asyncReadSome(network::buffer(_readBuffer, _readBuffer.size()),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                startRead();
            }
            if (bytes == 0) {
                std::clog << "Client disconnected" << std::endl;
                _socket.close();
            }
            handleRead(bytes);
        });
}
}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** TCPClient.cpp
*/

#include "TCPClient.hpp"

#include "IoContext.hpp"
#include "ZappyConstants.hpp"

namespace zappy::gui {
TCPClient::TCPClient(network::IOContext &ioc, const int port,
    const std::string &hostname, WorldState &worldState): _ioc(ioc), _socket(_ioc), _protocol(worldState)
{
    _readBuffer.resize(1024);
    _asyncReadBuffer.resize(1024);
    auto config = network::BASIC_CONFIG;
    config.context = "TCP-CLIENT";
    _logger.config(config);
    try {
        network::Endpoint endpoint(port, hostname);
        _socket.connect(endpoint);
        if (receive() == "WELCOME") {
            send("GRAPHIC");
        } else {
            _socket.close();
            throw std::runtime_error{"Received incorrect connection"};
        }
    } catch (std::exception &) {
        throw;
    }
}

void TCPClient::start()
{
    startRead();
}

void TCPClient::send(std::string data)
{
    _socket.write(network::buffer(data + data::PACKET_END),
        [this, &data](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                return;
            }

            if (bytes == 0) {
                _socket.close();
                return;
            }
            _logger.start(LogLevel::INFO) << "Sent: " << data << utils::END;
        });
}

std::string TCPClient::receive()
{
    bool done = false;

    while (!done) {
        _socket.read(network::buffer(_readBuffer, _readBuffer.size()),
            [this, &done](const std::error_code &err, const std::size_t &bytes) {
                if (err) {
                    std::cerr << err.message() << std::endl;
                    done = true;
                    return;
                }
                if (bytes == 0) {
                    _socket.close();
                    done = true;
                    return;
                }
                done = isTransmissionReady(bytes, _readBuffer);
            });
        pollAll();
    }

    const auto result = std::string{_transmission.data(), _transmission.size()};
    _transmission.clear();
    _logger.start(LogLevel::INFO) << "Received: " << result << utils::END;

    return result;
}

void TCPClient::pollAll() const
{
    _ioc.pollAll();
}

bool TCPClient::isTransmissionReady(const std::size_t &bytes,
    const std::string &buffer)
{
    const auto index = buffer.find(data::PACKET_END);

    if (index == std::string::npos && bytes != 0) {
        _transmission.append(_transmissionTemp.begin(),
            _transmissionTemp.end());
        _transmission.append(buffer.begin(),
            buffer.begin() + bytes);

        _transmissionTemp.clear();
        return false;
    }

    _transmission.append(buffer.begin(),
        buffer.begin() + index);

    _transmissionTemp.assign(
        buffer.begin() + index + data::PACKET_END.size(),
        buffer.end());
    return true;
}

void TCPClient::handleTransmission()
{
    _protocol.handleLine(_transmission);
    _transmission.clear();
    startRead();
}

void TCPClient::startRead()
{
    _socket.asyncReadSome(network::buffer(_asyncReadBuffer,
            _asyncReadBuffer.size()),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                _socket.close();
                return;
            }

            if (bytes == 0) {
                _socket.close();
                return;
            }

            if (!isTransmissionReady(bytes, _asyncReadBuffer)) {
                startRead();
            } else {
                _logger.start(LogLevel::INFO) << "Received: " << _transmission << utils::END;
                handleTransmission();
            }
        });
}
} // namespace zappy::gui

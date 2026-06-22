/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AClientSession.hpp"

#include "Logger.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

static constexpr std::size_t READ_BUFFER_SIZE = 1024;

AClientSession::AClientSession(
    const std::shared_ptr<network::ConnectedSocket> &socket): IClientSession{},
    _socket{socket}
{
    this->_readBuffer.resize(READ_BUFFER_SIZE);
    this->_asyncReadBuffer.resize(READ_BUFFER_SIZE);
    auto config = network::BASIC_CONFIG;
    config.context = "AI-SESSION";
    _logger.config(config);
}

void AClientSession::start()
{
    handleRead();
    _logger.start(LogLevel::INFO) << "AClientSession up" << utils::END;
}

void AClientSession::send(const std::string &data)
{
    _socket->write(network::buffer(data),
        [this, &data](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                _socket->close();
                return;
            }

            if (bytes == 0) {
                _socket->close();
                return;
            }
            _logger.start(LogLevel::INFO) << "Sent: " << data << utils::END;
        });
}

std::string AClientSession::receive()
{
    bool done = false;

    while (!done) {
    _socket->read(network::buffer(this->_readBuffer, this->_readBuffer.size()),
        [this, &done](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                done = true;
                return;
            }

            if (bytes == 0) {
                _socket->close();
                done = true;
                return;
            }

            done = isTransmissionReady(bytes);
        });
    }
    const auto result = std::string{_transmission.data(), _transmission.size()};
    _transmission.clear();
    _logger.start(LogLevel::INFO) << "Received: " << result << utils::END;

    return result;
}

void AClientSession::handleRead()
{
    _socket->asyncReadSome(network::buffer(_asyncReadBuffer, READ_BUFFER_SIZE),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                _socket->close();
                return;
            }

            if (bytes == 0) {
                _socket->close();
                return;
            }

            if (!isTransmissionReady(bytes)) {
                handleRead();
            } else {
                handleTransmission();
                handleRead();
                _logger.start(LogLevel::INFO) << "Received: " << _transmission << utils::END;
            }
        });
}

void AClientSession::handleWrite(const std::string &message)
{
    _socket->asyncWrite(network::buffer(message),
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                _socket->close();
                return;
            }

            if (bytes == 0) {
                _socket->close();
                return;
            }

            handleRead();
        });
}

bool AClientSession::isTransmissionReady(const size_t &bytes)
{
    const auto index = _asyncReadBuffer.find(data::PACKET_END);

    if (index == std::string::npos) {
        _transmission.append(_transmissionTemp.begin(),
            _transmissionTemp.end());
        _transmission.append(_asyncReadBuffer.begin(),
        _asyncReadBuffer.begin() + bytes);

        _transmissionTemp.clear();
        return false;
    }

    _transmission.append(_asyncReadBuffer.begin(),
        _asyncReadBuffer.begin() + index);

    _transmissionTemp.assign(
        _asyncReadBuffer.begin() + index + data::PACKET_END.size(),
        _asyncReadBuffer.end());
    return true;

}
}

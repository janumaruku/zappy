/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AClientSession.hpp"

#include "ZappyConstants.hpp"

namespace zappy::server {

static constexpr std::size_t READ_BUFFER_SIZE = 1024;

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
        [this](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                _socket->close();
                return;
            }

            if (bytes == 0)
                this->_socket->close();
        });
}

std::string AClientSession::receive()
{
    _socket->read(network::buffer(this->_readBuffer, this->_readBuffer.size()),
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

            if (!isTransmissionReady(bytes))
                receive();
        });

    const auto result = std::string{_transmission.data(), _transmission.size()};
    _transmission.clear();

    return result;
}

void AClientSession::handleRead()
{
    _socket->asyncReadSome(network::buffer(_asyncReadBuffer, READ_BUFFER_SIZE),
        [this](const std::error_code &ec, const std::size_t &bytes) {
            if (ec) {
                std::cerr << ec.message() << std::endl;
                _socket->close();
                return;
            }

            if (bytes == 0) {
                _socket->close();
                return;
            }

            if (!isTransmissionReady(bytes))
                handleRead();
            handleTransmission();
        });
}

void AClientSession::handleWrite(const std::string &message)
{
    _socket->asyncWrite(network::buffer(message),
        [this](const std::error_code &ec, const std::size_t &bytes) {
            if (ec) {
                std::cerr << ec.message() << std::endl;
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

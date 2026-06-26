/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef ACLIENTSESSION_HPP_
#define ACLIENTSESSION_HPP_

#include <memory>
#include <string>
#include "IClientSession.hpp"

namespace zappy::server {

class AClientSession: public IClientSession {
public:
    AClientSession() = delete;
    explicit AClientSession(
        const std::shared_ptr<network::ConnectedSocket> &socket);
    ~AClientSession() override = default;

    void start() override;
    void send(const std::string &data) override;
    std::string receive() override;

protected:
    std::shared_ptr<network::ConnectedSocket> _socket;
    std::string _readBuffer;
    std::string _asyncReadBuffer;
    std::string _transmissionTemp;
    std::string _transmission;

    void handleRead() override;
    void handleWrite(const std::string& message) override;

    bool isTransmissionReady(const size_t &bytes);

    utils::Logger _logger{"AI-SESSION", LogLevel::INFO, true};

};

}

#endif

/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef AISESSION_HPP_
    #define AISESSION_HPP_

    #include "AClientSession.hpp"
#include "Server.hpp"

namespace zappy::server {

class AISession : public AClientSession {
public:
    AISession() = delete;
    explicit AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
        Server &server, Player &player);
    ~AISession() override = default;

protected:
    void handleTransmission(const std::size_t &bytes) override;

private:
    Server &_server;
    Player &_player;
    uint _pending_commands = 0;
    // SteadyTimer _command_timer;
    // SteadyTimer _starvation_timer;
};

}

#endif

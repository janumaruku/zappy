/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef AISESSION_HPP_
    #define AISESSION_HPP_

    #include "IClientSession.hpp"
    #include "Temp.hpp"

namespace zappy::server {

constexpr char END_OF_TRANSMISSION = '\n';

class AISession : public IClientSession {
public:
    AISession() = delete;
    ~AISession() override = default;

    void start() override;
    void handleTransmission() override;

private:
    Server &_server;
    Player _player;
    uint _pending_commands;
    SteadyTimer _command_timer;
    SteadyTimer _starvation_timer;
};

}

#endif

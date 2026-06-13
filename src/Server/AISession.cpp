/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AISession.hpp"

namespace zappy::server {

void AISession::start()
{
    //remove this when you implement the override
    (void)_server;
    (void)_player;
    (void)_pending_commands;
    (void)_command_timer;
    (void)_starvation_timer;
}


void AISession::handleTransmission()
{
    _transmission.append(_readAsyncBuffer.begin(),
        _readAsyncBuffer.begin() + END_OF_TRANSMISSION);

    if (_transmission.ends_with(END_OF_TRANSMISSION)) {
        // call protocol
        _transmission.clear();
        return;
    }
    start();
}

} // namespace zappy::server

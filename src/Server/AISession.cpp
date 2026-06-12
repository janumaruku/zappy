/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AISession.hpp"

namespace zappy::server {

void AISession::handleTransmission()
{
    _transmission.append(_readAsyncBuffer.begin(),
        _readAsyncBuffer.begin() + bytes);

    if (_transmission.ends_with("\n")) {
        // call protocol
        _transmission.clear();
        return;
    }
    startRead();
}

} // namespace zappy::server

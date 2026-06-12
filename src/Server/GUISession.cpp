/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "GUISession.hpp"

namespace zappy::server {

void GUISession::handleTransmission(const std::size_t &bytes)
{
    this->_transmission.append(this->_readAsyncBuffer.begin(),
        this->_readAsyncBuffer.begin() + bytes);

    if (this->_transmission.ends_with("\n")) {
        // call protocol
        this->_transmission.clear();
        return;
    }
    this->start();
}

}

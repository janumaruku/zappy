/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AISession.hpp"
#include <cstddef>

namespace zappy::server {

void AISession::handleTransmission(const std::size_t &bytes)
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

} // namespace zappy::server

/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IoContext.tpp
*/

#pragma once

#include "IoContext.hpp"

namespace network {
template <typename Clock>
void IOContext::registerTimer(BasicWaitableTimer<Clock> &timer)
{
    struct TimerEntry entry {
        .id = timer.id(),
        .timePoint = static_cast<float>(timer.expiry().time_since_epoch().count()),
        .handler = timer.handler(),
        .cancellation = false
    };   
    _timerQueue.push(entry);
}   
}
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
        .timePoint = timer.expiry(),
        .handler = timer.handler(),
        .cancellation = false
    };   
    _timerQueue.emplace(entry);
}
}
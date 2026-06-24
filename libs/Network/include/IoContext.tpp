/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IoContext.tpp
*/

#pragma once

#include <cstdint>
#include "ContainerUtils.hpp"
#include "IoContext.hpp"

namespace network {
template <typename Clock>
void IOContext::registerTimer(BasicWaitableTimer<Clock> &timer)
{
    struct TimerEntry entry {
        .timePoint = static_cast<uint64_t>(timer.expiry().time_since_epoch().count()),
        .handler = timer.handler(),
        .cancellation = false
    };   
    _timerQueue.push(entry);
}

template<typename Clock>
void IOContext::cancelTimer(const std::chrono::time_point<Clock> &expiry)
{
    auto &values = container(_timerQueue);

    const auto it = std::ranges::find_if(values,
        [&expiry](const TimerEntry &entry) {
            return entry.timePoint == static_cast<uint64_t>(expiry.time_since_epoch().count());
        });
    if (it != values.end())
        it->cancellation = true;
}

}
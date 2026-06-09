/*
** EPITECH PROJECT, 2026
** Tek2
** File description:
** 
*/

#pragma once

#include "BasicWaitableTimer.hpp"
#include "IoContext.hpp"

namespace network {

template <typename Clock>
BasicWaitableTimer<Clock>::BasicWaitableTimer(const BasicWaitableTimer &&other) noexcept :
_id(other._id), _time_point(other._time_point), _ctx(other._ctx), _handler(other._handler) {}


template <typename Clock>
void BasicWaitableTimer<Clock>::asyncWait(Clock duration, const std::function<void()> &handler)
{
    _time_point = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() + duration).count();
    _handler = handler;
    _ctx.registerTimer(*this);
}

template <typename Clock>
void BasicWaitableTimer<Clock>::cancel() noexcept
{
    _ctx.cancelTimer(_id);
}

template <typename Clock>
void BasicWaitableTimer<Clock>::expiresAfter(Clock duration) const noexcept
{
    _time_point = std::chrono::duration_cast<std::chrono::seconds>(Clock::now() + duration).count();
    cancel();
}

template <typename Clock>
std::size_t BasicWaitableTimer<Clock>::expiry() const noexcept
{
    return _time_point;
}
}
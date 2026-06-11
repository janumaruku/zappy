/*
** EPITECH PROJECT, 2026
** Tek2
** File description:
** 
*/

#pragma once

#include "BasicWaitableTimer.hpp"

namespace network {

template <typename Clock>
BasicWaitableTimer<Clock>::BasicWaitableTimer(const BasicWaitableTimer &&other) noexcept :
_id(other._id), _expiry(other._expiry), _ioContext(other._ioContext), _handler(other._handler) {}

template <typename Clock>
BasicWaitableTimer<Clock>::BasicWaitableTimer(network::IOContext &ioContext, std::size_t id, std::chrono::duration<float> delayBeforeCall, std::function<void()> handler) :
    _id(id),
    _expiry(std::chrono::duration_cast<std::chrono::duration<float>>(delayBeforeCall).count()),
    _ioContext(ioContext),
    _handler(std::move(handler)) {}

template <typename Clock>
void BasicWaitableTimer<Clock>::asyncWait(Clock duration, const std::function<void()> &handler)
{
    _expiry = std::chrono::duration_cast<std::chrono::duration<float>>(duration).count();
    _handler = handler;
    _ioContext.registerTimer(*this);
}

template <typename Clock>
void BasicWaitableTimer<Clock>::cancel() noexcept
{
    _ioContext.cancelTimer(_id);
}

template <typename Clock>
void BasicWaitableTimer<Clock>::expiresAfter(const std::chrono::duration<float> duration) const noexcept
{
    _expiry = std::chrono::duration_cast<std::chrono::duration<float>>(Clock::now() + duration).count();
    cancel();
}

template <typename Clock>
std::chrono::duration<float> BasicWaitableTimer<Clock>::expiry() const noexcept
{
    return _expiry;
}
}
/*
** EPITECH PROJECT, 2026
** Tek2
** File description:
** 
*/

#pragma once

#include <chrono>
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
void BasicWaitableTimer<Clock>::asyncWait(const std::chrono::duration<float> &duration, const std::function<void()> &handler)
{
    _expiry = duration;
    _handler = handler;
    _ioContext.registerTimer(*this);
}

template <typename Clock>
void BasicWaitableTimer<Clock>::cancel() noexcept
{
    _ioContext.cancelTimer(_id);
}

template <typename Clock>
void BasicWaitableTimer<Clock>::expiresAfter(Clock::duration duration) noexcept
{
    auto timePoint = Clock::now() + duration;
    _expiry = static_cast<std::chrono::duration<float>>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            timePoint.time_since_epoch()
        ).count()
    );
    _expiry = duration;
    cancel();
}

template <typename Clock>
const std::chrono::duration<float> &BasicWaitableTimer<Clock>::expiry() const noexcept
{
    return _expiry;
}

template <typename Clock>
const std::size_t &BasicWaitableTimer<Clock>::id() const noexcept
{
    return _id;
}

template <typename Clock>
const std::function<void()> &BasicWaitableTimer<Clock>::handler() const noexcept
{
    return _handler;
}

}
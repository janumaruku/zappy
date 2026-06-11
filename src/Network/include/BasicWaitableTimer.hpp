/*
** EPITECH PROJECT, 2026
** Tek2
** File description:
** 
*/

#ifndef BASICWAITABLETIMER_HPP
#define BASICWAITABLETIMER_HPP

#include <cstddef>
#include <ctime>
#include <chrono>
#include <functional>
#include "IoContext.hpp"

namespace network {

template <typename Clock>
class BasicWaitableTimer {
public:
    BasicWaitableTimer() = default;
    BasicWaitableTimer(network::IOContext &ioContext, std::size_t id, std::chrono::duration<float> delayBeforeCall, std::function<void()> handler = {});

    BasicWaitableTimer(const BasicWaitableTimer &) = delete;
    BasicWaitableTimer(const BasicWaitableTimer &&other) noexcept;

    void asyncWait(Clock duration, const std::function<void()> &handler);
    void expiresAfter(std::chrono::duration<float> duration) const noexcept;
    void cancel() noexcept;
    [[nodiscard]] std::chrono::duration<float> expiry() const noexcept;

    ~BasicWaitableTimer() = default;
private:
    std::size_t _id;
    std::chrono::duration<float> _expiry;
    network::IOContext &_ioContext;
    std::function<void()> _handler;
};

}

#endif //BASICWAITABLETIMER_HPP
#include "BasicWaitableTimer.tpp"
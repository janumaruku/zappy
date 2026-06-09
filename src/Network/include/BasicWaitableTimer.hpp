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

    BasicWaitableTimer(const BasicWaitableTimer &) = delete;
    BasicWaitableTimer(const BasicWaitableTimer &&other) noexcept;

    void asyncWait(Clock duration, const std::function<void()> &handler);
    void expiresAfter(Clock duration) const noexcept;
    void cancel() noexcept;
    [[nodiscard]] std::size_t expiry() const noexcept;

    ~BasicWaitableTimer() = default;
private:
    std::size_t _id;
    std::time_t _time_point;
    network::IOContext &_ioContext;
    std::function<void()> _handler;
};

}

#endif //BASICWAITABLETIMER_HPP
#include "BasicWaitableTimer.tpp"
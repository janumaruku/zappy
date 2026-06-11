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
using Duration = Clock::duration;
    BasicWaitableTimer() = default;
    BasicWaitableTimer(network::IOContext &ioContext, std::size_t id, std::function<void()> handler = {});

    BasicWaitableTimer(const BasicWaitableTimer &) = delete;
    BasicWaitableTimer(const BasicWaitableTimer &&other) noexcept;

    void asyncWait(const Duration &duration, const std::function<void()> &handler);
    void expiresAfter(Clock::duration duration) noexcept;
    void cancel() noexcept;
    [[nodiscard]] std::chrono::time_point<Clock> expiry() const noexcept;
    [[nodiscard]] const std::size_t &id() const noexcept;
    [[nodiscard]] const std::function<void()> &handler() const noexcept;

    ~BasicWaitableTimer() = default;
private:
    std::size_t _id;
    std::chrono::time_point<Clock> _expiry;
    network::IOContext &_ioContext;
    std::function<void()> _handler;
};

}

#endif //BASICWAITABLETIMER_HPP
#include "BasicWaitableTimer.tpp"
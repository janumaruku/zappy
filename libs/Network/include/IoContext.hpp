/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#pragma once

#include <chrono>
#include <functional>
#include <poll.h>
#include <queue>
#include <unordered_map>
#include <vector>
#include <ctime>

#include "ConnectedSocket.hpp"

namespace network {

template <typename Clock>
class BasicWaitableTimer;

struct TimerEntry {
    std::size_t id;
    float timePoint;
    std::function<void()> handler;
    bool cancellation;
};

struct TimerEntryCompare
{
  constexpr bool
  operator()(const TimerEntry &x, const TimerEntry &y) const
  { return x.timePoint > y.timePoint; }
};

/**
 * @class IOContext
 * @brief The event loop that drives all asynchronous operations in the library.
 *
 * @c IOContext keeps a list of file descriptors to watch and a queue of pending
 * callbacks per descriptor. When you call @ref ConnectedSocket::asyncReadSome,
 * @ref ConnectedSocket::asyncWrite, or @ref Acceptor::asyncAccept, the operation
 * is not executed immediately. Instead, the callback is registered here via
 * @ref postRead or @ref postWrite. The actual execution happens when you tick
 * the loop with @ref run, @ref poll, or @ref pollAll.
 *
 * See @ref async_model for a detailed explanation of how this works.
 */
class IOContext {
    enum class OpType: uint8_t {
        READ,
        WRITE
    };

public:
    /// @brief Callback type invoked when a file descriptor is ready for I/O.
    using OnFileDescriptorReady = std::function<void()>;

    /// @brief Internal pair of an operation type and its callback. Not intended for direct use.
    using PendingOperation = std::pair<OpType, OnFileDescriptorReady>;

    IOContext() = default;

    /**
     * @brief Adds a file descriptor to the watch list.
     * @param fileDescriptor The file descriptor to watch.
     */
    void registerFileDescriptor(const int &fileDescriptor);

    /**
     * @brief Removes a file descriptor from the watch list and discards its pending operations.
     * @param fileDescriptor The file descriptor to remove.
     */
    void unregisterFileDescriptor(const int &fileDescriptor);

    /**
     * @brief Enqueues a callback to be called when @p fileDescriptor is readable.
     * @param fileDescriptor The file descriptor to watch for readability.
     * @param handler        Callback invoked when the descriptor is ready to read.
     */
    void postRead(const int &fileDescriptor,
        const OnFileDescriptorReady &handler);

    /**
     * @brief Enqueues a callback to be called when @p fileDescriptor is writable.
     * @param fileDescriptor The file descriptor to watch for writability.
     * @param handler        Callback invoked when the descriptor is ready to write.
     */
    void postWrite(const int &fileDescriptor,
        const OnFileDescriptorReady &handler);

    /**
     * @brief Starts the event loop and blocks until @ref stop is called.
     *
     * On each iteration, calls @c poll(2) and dispatches one ready callback per
     * file descriptor. This is the normal entry point for a server.
     */
    void run();

    /**
     * @brief Signals the event loop to stop after the current iteration completes.
     *
     * Safe to call from inside a callback.
     */
    void stop() noexcept;

    /**
     * @brief Runs a single iteration of the event loop and returns immediately.
     *
     * Calls @c poll(2) once and dispatches one ready callback per file descriptor.
     * Useful when you need to interleave the event loop with other logic.
     */
    void poll();

    /**
     * @brief Drains all pending operations without blocking on @c poll(2).
     *
     * Returns once the pending operation queue is empty.
     */
    void pollAll();

    
    template <typename Clock>
    void registerTimer(BasicWaitableTimer<Clock> &timer);

    void cancelTimer(const std::size_t &id);

    private:
    std::vector<pollfd> _pollFds;                                        ///< List of file descriptors watched by @c poll(2).
    std::unordered_map<int, std::queue<PendingOperation>> _pendingOperations; ///< Pending callbacks per file descriptor.
    bool _stop    = false; ///< Flag set by @ref stop to exit the run loop.
    bool _running = false; ///< True while @ref run is executing.
    std::priority_queue<TimerEntry, std::vector<TimerEntry>, TimerEntryCompare> _timerQueue;

    void updateEventType(const int &fileDescriptor);
    void handleReadyFileDescriptors();
    void triggerHandler(const int &itt);

    void drainExpiredTimers();
};
}

#include "IoContext.tpp"
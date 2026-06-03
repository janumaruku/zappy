/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#ifndef MYFTP_IOCONTEXT_HPP
#define MYFTP_IOCONTEXT_HPP

#include <functional>
#include <poll.h>
#include <unordered_map>
#include <vector>

#include "ConnectedSocket.hpp"

namespace network {
class IOContext {
    enum class OpType: uint8_t {
        READ,
        WRITE
    };

public:
    using OnFileDescriptorReady = std::function<void()>;

    using PendingOperation = std::pair<OpType, OnFileDescriptorReady>;

    IOContext() = default;

    void registerFileDescriptor(const int &fileDescriptor);

    void unregisterFileDescriptor(const int &fileDescriptor);

    void postRead(const int &fileDescriptor,
        const OnFileDescriptorReady &handler);

    void postWrite(const int &fileDescriptor,
        const OnFileDescriptorReady &handler);

    void run();

    void stop() noexcept;

    void poll();

    void pollAll();

private:
    std::vector<pollfd> _pollFds;
    std::unordered_map<int, std::queue<PendingOperation>> _pendingOperations;
    bool _stop    = false;
    bool _running = false;

    void updateEventType(const int &fileDescriptor);

    void handleReadyFileDescriptors();

    void triggerHandler(const int &itt);
};
}

#endif //MYFTP_IOCONTEXT_HPP

/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IoContext
*/

#include "IoContext.hpp"

#include <algorithm>
#include <ranges>
#include <system_error>

#include "constants.hpp"

namespace network {
void IOContext::registerFileDescriptor(const int &fileDescriptor)
{
    _pollFds.push_back({
        .fd      = fileDescriptor,
        .events  = POLLIN,
        .revents = 0,
    });
}

void IOContext::unregisterFileDescriptor(const int &fileDescriptor)
{
    const auto itt = std::ranges::find_if(_pollFds,
        [fileDescriptor](const pollfd &pollFd) {
            return pollFd.fd == fileDescriptor;
        });

    if (_pendingOperations.contains(itt->fd))
        _pendingOperations.erase(itt->fd);

    if (itt != _pollFds.end())
        _pollFds.erase(itt);
}

void IOContext::postRead(const int &fileDescriptor,
    const OnFileDescriptorReady &handler)
{
    _pendingOperations[fileDescriptor].emplace(OpType::READ, handler);
    updateEventType(fileDescriptor);
}

void IOContext::postWrite(const int &fileDescriptor,
    const OnFileDescriptorReady &handler)
{
    _pendingOperations[fileDescriptor].emplace(OpType::WRITE, handler);
    updateEventType(fileDescriptor);
}

void IOContext::run()
{
    _running = true;

    while (true) {
        if (::poll(_pollFds.data(), _pollFds.size(), 10) == -1)
            throw std::runtime_error(
                utils::RED + "Error: " + utils::RESET + std::string{
                    strerror(errno)
                });

        handleReadyFileDescriptors();

        if (_stop && std::ranges::all_of(_pendingOperations,
            [](const auto &entry) {
                return entry.second.empty();
            }))
            break;
    }

    _running = false;
}

void IOContext::stop() noexcept
{
    _stop = true;
}

void IOContext::poll()
{
    if (_running)
        throw std::runtime_error(
            utils::RED + "Error: " + utils::RESET +
            "The IOContext loop is already running");

    if (::poll(_pollFds.data(), _pollFds.size(), 10) == -1)
        throw std::runtime_error(
            utils::RED + "Error: " + utils::RESET + std::string
            {strerror(errno)});

    handleReadyFileDescriptors();
}

void IOContext::pollAll()
{
    if (_running)
        throw std::runtime_error(
            utils::RED + "Error: " + utils::RESET +
            "The IOContext loop is already running");

    while (::poll(_pollFds.data(), _pollFds.size(), 0) > 0)
        handleReadyFileDescriptors();
}

void IOContext::updateEventType(const int &fileDescriptor)
{
    if (_pendingOperations.contains(fileDescriptor) &&
        !_pendingOperations.at(fileDescriptor).empty()) {
        const OpType opType = _pendingOperations.at(fileDescriptor).front().
                                                 first;
        const auto itt = std::ranges::find_if(_pollFds,
            [fileDescriptor](const pollfd &pollFd) {
                return pollFd.fd == fileDescriptor;
            });

        if (itt == _pollFds.end())
            return;

        itt->events = opType == OpType::READ
            ? POLLIN
            : POLLOUT;
    }
}

void IOContext::handleReadyFileDescriptors()
{
    std::size_t itt = 0;

    while (itt < _pollFds.size()) {
        if (_pollFds[itt].revents & (POLLHUP | POLLERR | POLLNVAL)) {
            _pendingOperations.erase(_pollFds[itt].fd);
            _pollFds.erase(_pollFds.begin() + itt);
            continue;
        }

        triggerHandler(itt);

        if (_stop && _pollFds.empty())
            break;

        ++itt;
    }
}

void IOContext::triggerHandler(const int &itt)
{
    const int fd = _pollFds[itt].fd;

    if (_pollFds[itt].revents & (POLLIN | POLLOUT) && (
        _pendingOperations.contains(fd) && !_pendingOperations.
                                            at(fd).empty())) {
        const auto [opType, handler] = _pendingOperations.at(fd).
            front();
        _pendingOperations.at(fd).pop();

        handler();
        updateEventType(fd);
    }
}
}

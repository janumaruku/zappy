/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include <algorithm>
#include <initializer_list>
#include <cctype>
#include <ranges>
#include <cstddef>
#include <chrono>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <vector>
#include <functional>

#include "StringUtils.hpp"
#include "ZappyConstants.hpp"
#include "ConnectedSocket.hpp"
#include "Timer.hpp"
#include "AISession.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
AISession::AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
    Server &server, Player &player): AClientSession{socket}, _server{server}, _player{player},
    _command_timer(socket->getIOContext()), _starvation_timer(socket->getIOContext()),
    _protocolHandler(std::make_unique<AIProtocolHandler>())
{
}

AISession::~AISession() = default;

Player &AISession::getPlayer() noexcept
{
    return _player;
}

Server &AISession::getServer() noexcept
{
    return _server;
}

void AISession::freeze() noexcept
{
    _frozen = true;
}

void AISession::unfreeze() noexcept
{
    _frozen = false;
}

bool AISession::isFrozen() const noexcept
{
    return _frozen;
}

void AISession::scheduleTask(const uint &durationConstant,
    const std::function<void()> &task)
{
    _command_timer.asyncWait(std::chrono::high_resolution_clock::duration(
        durationConstant / _server.getFrequency()),
    [task]() {
        task();
    });
}

void AISession::handleTransmission()
{
    if (_pending_commands >= MAX_PENDING_COMMANDS)
        return;

    std::vector<std::string> splittedLine = utils::StringUtils::split(_transmission);
    _commandQueue.push(splittedLine);
    _pending_commands++;
    if (_pending_commands == 1)
        executeNext();
    
    _transmission.clear();
}

void AISession::executeNext()
{
    const auto &command = _commandQueue.front();

    _protocolHandler->handleLine(command, *this);
}

void AISession::onCommandComplete()
{
    _pending_commands--;
    _commandQueue.pop();
    if (_commandQueue.empty())
        return;
    executeNext();
}

void AISession::scheduleResponse(const uint &durationConstant, const std::string &response)
{
    _command_timer.asyncWait(std::chrono::high_resolution_clock::duration(durationConstant / _server.getFrequency()),
    [this, response]() {
        send(response);
        onCommandComplete();
    });
}

const Player &AISession::getPlayer() const noexcept
{
    return _player;
}

const Server &AISession::getServer() const noexcept
{
    return _server;
}

} // namespace zappy::server

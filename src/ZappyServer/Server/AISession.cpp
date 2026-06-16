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
#include "StringUtils.hpp"
#include "ZappyConstants.hpp"
#include "AISession.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
AISession::AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
    Server &server, Player &player): AClientSession{socket}, _server{server}, _player{player}
{
}

void AISession::handleTransmission()
{
    std::vector<std::string> splittedLine = utils::StringUtils::split(_transmission);
    if (_pending_commands >= MAX_PENDING_COMMANDS)
        return;

    const auto &commandPrefix = splittedLine[0];
    const auto &availableCommands = _protocolHandler.getAvailableCommands();

    auto it = std::ranges::find_if(availableCommands,
        [availableCommands, commandPrefix](const std::string &str) {
            return str == commandPrefix;
        }
    );
    if (it == availableCommands.end()) {
        send(COMMAND_NOT_FOUND);
        return;
    }
    bool wasEmpty = _commandQueue.empty();
    _commandQueue.push(splittedLine);
    _pending_commands++;
    if (wasEmpty)
        executeNext();
    
    scheduleResponse(RESPONSE_TIME, PLACEHOLDER_SERVER_RESPONSE);
    _transmission.clear();
}


void AISession::executeNext()
{
    const auto &command = _commandQueue.front();

    _protocolHandler.handleLine(command, *this);
}

void AISession::onCommandComplete()
{
    _pending_commands--;
    if (_commandQueue.empty())
        return;
    executeNext();
}


void AISession::scheduleResponse(const uint &durationConstant, const std::string &response)
{
    _command_timer.asyncWait(std::chrono::high_resolution_clock::duration(durationConstant / COMMAND_TRIGGER_DIVISOR),
    [this, response](){
        send(response);
    });
    onCommandComplete();
}


const Player &AISession::getPlayer() const noexcept
{
    return _player;
}

const Server &AISession::getServer() const noexcept
{
    return _server;
}

// free functions

} // namespace zappy::server

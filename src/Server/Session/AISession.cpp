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
#include <sys/types.h>
#include <vector>
#include "AISession.hpp"

namespace zappy::server {

void AISession::start()
{
    //remove this when you implement the override
    (void)_server;
    (void)_player;
    (void)_pending_commands;
    (void)_command_timer;
    (void)_starvation_timer;
}


void AISession::handleTransmission()
{
    _transmission.append(_readAsyncBuffer.begin(),
        _readAsyncBuffer.begin() + END_OF_TRANSMISSION);

    if (!_transmission.ends_with(END_OF_TRANSMISSION)) {
        start();
        return;
    }

    std::vector<std::string> splittedLine = sanitizedSplit(_transmission);
    if (_pending_commands >= MAX_PENDING_COMMANDS)
        return;

    // const auto &commandPrefix = splittedLine[0];

    if (false /* if !prefix exists in map */) {
        _writeQueue.push(COMMAND_NOT_FOUND);
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
    const auto prefix = command[0];

    // execute(command, *this);
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
        _writeQueue.push(response);
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
std::size_t AISession::getResultSize(const std::string &str)
{
    std::size_t count = 0;
    std::size_t strSize = str.size();
    std::size_t i = 0;

    for (; i < strSize; i++) {
        if (!std::isalpha(str[i]))
            continue;
        count++;
        for (; i != strSize && std::isalpha(str[i + 1]); i++);
    }
    return count;
}

std::vector<std::string> AISession::sanitizedSplit(const std::string &str)
{
    std::vector<std::string> result;

    if (str == "\n") {
        result.emplace_back("\n");
        return result;
    }

    std::size_t resultSize = getResultSize(str);
    std::size_t strSize = str.size();
    std::string buf;
    std::size_t j = 0;

    for (std::size_t i = 0; i != resultSize; i++) {
        for (; j < strSize && !std::isalpha(str[j]); j++);
        while (j < strSize && std::isalpha(str[j]))
            buf.push_back(str[j++]);
        result.push_back(buf);
        buf.clear();
    }
    return result;
}
// free functions

} // namespace zappy::server

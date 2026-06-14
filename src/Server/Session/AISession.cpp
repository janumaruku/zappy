/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AISession.hpp"
#include <algorithm>
#include <initializer_list>
#include <cctype>
#include <ranges>
#include <cstddef>
#include <sys/types.h>

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

    if (_transmission.ends_with(END_OF_TRANSMISSION)) {
        // call protocol
        _transmission.clear();
        return;
    }
    start();
}

std::size_t AISession::getResultSize(const std::string &str)
{
    std::size_t count = 0;
    std::size_t strSize = str.size();
    size_t i = 0;

    for (; str[i]; i++) {
        auto currentPos = i;
        for (; i + 1 < strSize && !std::isalpha(str[i + 1]); i++);
        count += currentPos != i;
    }
    return count;
}


std::vector<std::string> AISession::sanitizedSplit(const std::string &str) 
{
    std::vector<std::string> result;

    if (str == "\n") {
        result.emplace_back ("\n");
        return result;
    }

    std::string buf;
    std::size_t resultSize = getResultSize(str);
    size_t j = 0;

    for (size_t i = 0; i != resultSize; i++) {
        for (; str[j]; j++) {
            if (!std::isalpha(str[j])){
                j++;
                break;
            }
            std::cout << "current char:\"" << str[j] << "\"" << std::endl;
            buf.push_back(str[j]);
        }
        result.push_back(buf);
        buf.clear();
        std::cout << "vec[i] = " << result[i] << std::endl;
    }
    return result;
}

} // namespace zappy::server

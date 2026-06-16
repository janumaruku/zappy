/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.cpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "BroadcastCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool BroadcastCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool BroadcastCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> BroadcastCommand<Args...>::create()
{
    return std::make_unique<BroadcastCommand<Args...>>(BroadcastCommand<Args...>());
}

// specialisations

template<>
bool BroadcastCommand<AISession &, const std::vector<std::string> &>::
execute(AISession &session, const std::vector<std::string> &cmd)
{
    std::string data;
    std::size_t words = cmd.size();

    for (std::size_t i = 1; i != words; i++) {
        data.append(cmd[i]);
        if (i < words)
            data.append(" ");
    }
    session.send(data);
    return true;
}

}
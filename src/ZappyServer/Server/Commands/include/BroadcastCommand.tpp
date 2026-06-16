/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.cpp
*/

#pragma once

#include <memory>
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

}
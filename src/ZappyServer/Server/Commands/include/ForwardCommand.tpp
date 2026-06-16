/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.cpp
*/

#pragma once

#include <memory>
#include "ForwardCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool ForwardCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool ForwardCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> ForwardCommand<Args...>::create()
{
    return std::make_unique<ForwardCommand<Args...>>(ForwardCommand<Args...>());
}

}
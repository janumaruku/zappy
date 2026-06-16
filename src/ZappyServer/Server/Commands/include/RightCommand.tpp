/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.cpp
*/

#pragma once

#include <memory>
#include "RightCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool RightCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool RightCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> RightCommand<Args...>::create()
{
    return std::make_unique<RightCommand<Args...>>(RightCommand<Args...>());
}

}
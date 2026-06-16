/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.cpp
*/

#pragma once

#include <memory>
#include "LeftCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool LeftCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool LeftCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> LeftCommand<Args...>::create()
{
    return std::make_unique<LeftCommand<Args...>>(LeftCommand<Args...>());
}

}
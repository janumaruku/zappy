/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommand.cpp
*/

#pragma once

#include <memory>
#include "IncantationCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool IncantationCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool IncantationCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> IncantationCommand<Args...>::create()
{
    return std::make_unique<IncantationCommand<Args...>>(IncantationCommand<Args...>());
}

}
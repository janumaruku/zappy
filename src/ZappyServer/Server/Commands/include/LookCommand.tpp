/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.cpp
*/

#pragma once

#include <memory>
#include "LookCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool LookCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool LookCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> LookCommand<Args...>::create()
{
    return std::make_unique<LookCommand<Args...>>(LookCommand<Args...>());
}

}
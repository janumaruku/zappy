/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommand.cpp
*/

#pragma once

#include <memory>
#include "ConnectNbrCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool ConnectNbrCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool ConnectNbrCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> ConnectNbrCommand<Args...>::create()
{
    return std::make_unique<ConnectNbrCommand<Args...>>(ConnectNbrCommand<Args...>());
}

}
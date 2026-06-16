/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MctCommand.cpp
*/

#pragma once

#include <memory>
#include "MctCommand.hpp"

namespace zappy::gui {

template<typename... Args>
bool MctCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool MctCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> MctCommand<Args...>::create()
{
    return std::make_unique<MctCommand<Args...>>(MctCommand<Args...>());
}

}
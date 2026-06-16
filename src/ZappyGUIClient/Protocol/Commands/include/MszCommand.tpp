/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MszCommand.cpp
*/


#pragma once

#include <memory>
#include "MszCommand.hpp"

namespace zappy::gui {

template<typename... Args>
bool MszCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool MszCommand<Args...>::operator()(Args...)
{
    return true;
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> MszCommand<Args...>::create()
{
    return std::make_unique<MszCommand<Args...>>(MszCommand<Args...>());
}

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BctCommand.cpp
*/

#pragma once

#include <memory>
#include "BctCommand.hpp"

namespace zappy::gui {

template<typename... Args>
bool BctCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool BctCommand<Args...>::operator()(Args...)
{
    return true;
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> BctCommand<Args...>::create()
{
    return std::make_unique<BctCommand<Args...>>(BctCommand<Args...>());
}

}
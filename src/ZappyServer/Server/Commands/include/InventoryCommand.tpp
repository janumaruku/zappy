/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommand.cpp
*/

#pragma once

#include <memory>
#include "InventoryCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool InventoryCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool InventoryCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> InventoryCommand<Args...>::create()
{
    return std::make_unique<InventoryCommand<Args...>>(InventoryCommand<Args...>());
}

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.cpp
*/

#pragma once

#include <memory>
#include "AISession.hpp"
#include "ForkCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool ForkCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool ForkCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> ForkCommand<Args...>::create()
{
    return std::make_unique<ForkCommand<Args...>>(ForkCommand<Args...>());
}

// specialisations

template<>
bool ForkCommand<AISession &, const std::vector<std::string> &>::
execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send(cmd[0]);
    return true;
}

}
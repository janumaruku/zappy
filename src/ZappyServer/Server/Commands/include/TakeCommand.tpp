/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommand.cpp
*/

#pragma once

#include <memory>
#include "AISession.hpp"
#include "TakeCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool TakeCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool TakeCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> TakeCommand<Args...>::create()
{
    return std::make_unique<TakeCommand<Args...>>(TakeCommand<Args...>());
}

// specialisations

template<>
bool TakeCommand<AISession &, const std::vector<std::string> &>::
execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send(cmd[0] + " " + cmd[1]);
    return true;
}


}
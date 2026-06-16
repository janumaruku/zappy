/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.cpp
*/

#pragma once

#include <memory>
#include "AISession.hpp"
#include "EjectCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool EjectCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool EjectCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> EjectCommand<Args...>::create()
{
    return std::make_unique<EjectCommand<Args...>>(EjectCommand<Args...>());
}

// specialisations

template<>
bool EjectCommand<AISession &, const std::vector<std::string> &>::
execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send(cmd[0]);
    return true;
}

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.cpp
*/

#pragma once

#include <memory>
#include "AISession.hpp"
#include "SetCommand.hpp"

namespace zappy::server {

template<typename... Args>
bool SetCommand<Args...>::execute(Args...)
{
    return true;
}

template<typename... Args>
bool SetCommand<Args...>::operator()(Args...args)
{
    return execute(args...);
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>> SetCommand<Args...>::create()
{
    return std::make_unique<SetCommand<Args...>>(SetCommand<Args...>());
}

// specialisations

template<>
bool SetCommand<AISession &, const std::vector<std::string> &>::
execute(AISession &session, const std::vector<std::string> &cmd)
{
    session.send(cmd[0] + " " + cmd[1]);
    return true;
}


}
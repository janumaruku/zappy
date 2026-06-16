/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MszCommand.cpp
*/

#include "MszCommand.hpp"
#include <memory>

namespace zappy::gui {

template<typename... Args>
bool MszCommand::execute(Args...args)
{
    return true;
}

template<typename... Args>

bool MszCommand::operator()(Args...args)
{
    return true;
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>>> create()
{
    return std::make_unique<ICommand<Args...>>(MszCommand<Args...>());
}

}
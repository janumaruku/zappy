/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MctCommand.cpp
*/

#include "MctCommand.hpp"
#include <memory>

namespace zappy::gui {

template<typename... Args>
bool MctCommand::execute(Args...args)
{
    return true;
}

template<typename... Args>

bool MctCommand::operator()(Args...args)
{
    return true;
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>>> create()
{
    return std::make_unique<ICommand<Args...>>(MctCommand<Args...>());
}

}
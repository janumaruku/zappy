/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BctCommand.cpp
*/

#include "BctCommand.hpp"
#include <memory>

namespace zappy::gui {

template<typename... Args>
bool BctCommand::execute(Args...args)
{
    return true;
}

template<typename... Args>

bool BctCommand::operator()(Args...args)
{
    return true;
}

template<typename... Args>
std::unique_ptr<ICommand<Args...>>> create()
{
    return std::make_unique<ICommand<Args...>>(BctCommand<Args...>());
}

}
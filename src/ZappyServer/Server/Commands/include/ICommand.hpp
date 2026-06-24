/*
** EPITECH PROJECT, 2026
**
** File description:
**
*/

#pragma once

#include <memory>
#include <vector>

namespace zappy::server {

template <typename... Args>
class ICommand {
public:
    virtual ~ICommand() = default;

    virtual bool execute(Args... args) = 0;

    virtual bool operator()(Args... args) = 0;
};


}

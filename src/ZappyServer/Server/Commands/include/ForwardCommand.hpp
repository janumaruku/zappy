/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class ForwardCommand : public ICommand<Args...> {
public:
    ForwardCommand() = default;

    ~ForwardCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
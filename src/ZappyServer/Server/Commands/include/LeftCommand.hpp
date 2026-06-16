/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class LeftCommand : public ICommand<Args...> {
public:
    LeftCommand() = default;

    ~LeftCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
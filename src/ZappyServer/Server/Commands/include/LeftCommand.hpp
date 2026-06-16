/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class LeftCommandCommand : public ICommand<Args...> {
public:
    LeftCommandCommand() = default;

    ~LeftCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
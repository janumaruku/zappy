/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class RightCommand : public ICommand<Args...> {
public:
    RightCommand() = default;

    ~RightCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
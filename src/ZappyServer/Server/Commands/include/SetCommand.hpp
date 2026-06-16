/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class SetCommandCommand : public ICommand<Args...> {
public:
    SetCommandCommand() = default;

    ~SetCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
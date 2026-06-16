/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class SetCommand : public ICommand<Args...> {
public:
    SetCommand() = default;

    ~SetCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
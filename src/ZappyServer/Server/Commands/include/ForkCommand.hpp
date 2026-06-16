/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class ForkCommand : public ICommand<Args...> {
public:
    ForkCommand() = default;

    ~ForkCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
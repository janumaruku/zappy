/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class ForkCommandCommand : public ICommand<Args...> {
public:
    ForkCommandCommand() = default;

    ~ForkCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
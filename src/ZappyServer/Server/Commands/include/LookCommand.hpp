/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class LookCommandCommand : public ICommand<Args...> {
public:
    LookCommandCommand() = default;

    ~LookCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
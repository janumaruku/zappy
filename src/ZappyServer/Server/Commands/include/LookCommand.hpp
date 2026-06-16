/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class LookCommand : public ICommand<Args...> {
public:
    LookCommand() = default;

    ~LookCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
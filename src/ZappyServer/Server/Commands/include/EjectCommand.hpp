/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class EjectCommand : public ICommand<Args...> {
public:
    EjectCommand() = default;

    ~EjectCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
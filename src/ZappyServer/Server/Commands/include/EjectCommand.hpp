/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EjectCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class EjectCommandCommand : public ICommand<Args...> {
public:
    EjectCommandCommand() = default;

    ~EjectCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class ConnectNbrCommand : public ICommand<Args...> {
public:
    ConnectNbrCommand() = default;

    ~ConnectNbrCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class ConnectNbrCommandCommand : public ICommand<Args...> {
public:
    ConnectNbrCommandCommand() = default;

    ~ConnectNbrCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
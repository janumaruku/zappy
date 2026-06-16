/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class BroadcastCommand : public ICommand<Args...> {
public:
    BroadcastCommand() = default;

    ~BroadcastCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class TakeCommandCommand : public ICommand<Args...> {
public:
    TakeCommandCommand() = default;

    ~TakeCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
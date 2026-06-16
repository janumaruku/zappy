/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class IncantationCommandCommand : public ICommand<Args...> {
public:
    IncantationCommandCommand() = default;

    ~IncantationCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
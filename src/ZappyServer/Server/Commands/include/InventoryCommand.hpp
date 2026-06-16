/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class InventoryCommandCommand : public ICommand<Args...> {
public:
    InventoryCommandCommand() = default;

    ~InventoryCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
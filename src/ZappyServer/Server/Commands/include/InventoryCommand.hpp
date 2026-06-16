/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class InventoryCommand : public ICommand<Args...> {
public:
    InventoryCommand() = default;

    ~InventoryCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
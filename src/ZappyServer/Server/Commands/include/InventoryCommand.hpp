/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** InventoryCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class InventoryCommand : public ICommand {
public:
    InventoryCommand() = default;

    ~InventoryCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;
};

}
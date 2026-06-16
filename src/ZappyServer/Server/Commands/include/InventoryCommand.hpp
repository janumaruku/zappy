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
        const std::vector<std::string> &cmd,
        AISession &session) override;

    bool execute(const std::vector<std::string> &cmd,
        AISession &session) override;

    static std::unique_ptr<ICommand> create();

};

}
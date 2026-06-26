/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** InventoryCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class InventoryCommand : public AIProtocolCommand {
public:
    InventoryCommand() = default;

    ~InventoryCommand() override = default;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
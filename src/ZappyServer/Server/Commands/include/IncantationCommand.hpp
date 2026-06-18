/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IncantationCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class IncantationCommand : public AIProtocolCommand {
public:
    IncantationCommand() = default;

    ~IncantationCommand() override;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
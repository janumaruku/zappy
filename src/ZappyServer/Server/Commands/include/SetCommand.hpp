/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SetCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class SetCommand : public AIProtocolCommand {
public:
    SetCommand() = default;

    ~SetCommand() override = default;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
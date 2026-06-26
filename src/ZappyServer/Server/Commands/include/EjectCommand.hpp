/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** EjectCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class EjectCommand : public AIProtocolCommand {
public:
    EjectCommand() = default;

    ~EjectCommand() override = default;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
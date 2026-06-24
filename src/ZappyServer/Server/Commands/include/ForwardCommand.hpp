/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class ForwardCommand : public AIProtocolCommand {
public:
    ForwardCommand() = default;

    ~ForwardCommand() override = default;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
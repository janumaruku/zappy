/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** LookCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class LookCommand : public AIProtocolCommand {
public:
    LookCommand() = default;

    ~LookCommand() override = default;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
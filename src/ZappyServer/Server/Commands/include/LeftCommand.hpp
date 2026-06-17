/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LeftCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class LeftCommand : public AIProtocolCommand {
public:
    LeftCommand() = default;

    ~LeftCommand() override;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
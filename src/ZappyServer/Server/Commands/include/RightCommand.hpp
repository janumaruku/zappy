/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class RightCommand : public AIProtocolCommand {
public:
    RightCommand() = default;

    ~RightCommand() override;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
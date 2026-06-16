/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommand.hpp
*/

#pragma once

#include "ICommand.hpp"
#include "AIProtocolHandler.hpp"

namespace zappy::server {
class TakeCommand : public AIProtocolCommand {
public:
    TakeCommand() = default;

    ~TakeCommand() override;

    bool operator()(AISession &, const std::vector<std::string> &) override;

    bool execute(AISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<AIProtocolCommand> create();

};

}
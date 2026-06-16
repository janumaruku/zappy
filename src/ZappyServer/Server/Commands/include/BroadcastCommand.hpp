/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class BroadcastCommand : public ICommand {
public:
    BroadcastCommand() = default;

    ~BroadcastCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;
};

}
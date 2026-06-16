/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForwardCommand.hpp
*/

#pragma once

#include "AISession.hpp"
#include "ICommand.hpp"

namespace zappy::server {

class ForwardCommand : public ICommand {
public:
    ForwardCommand() = default;

    ~ForwardCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;
};

}
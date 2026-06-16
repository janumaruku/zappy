/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SetCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class SetCommand : public ICommand {
public:
    SetCommand() = default;

    ~SetCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;
};

}
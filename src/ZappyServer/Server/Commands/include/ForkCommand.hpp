/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ForkCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class ForkCommand : public ICommand {
public:
    ForkCommand() = default;

    ~ForkCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;
};

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class LookCommand : public ICommand {
public:
    LookCommand() = default;

    ~LookCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;
};

}
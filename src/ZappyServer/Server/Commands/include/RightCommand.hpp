/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class RightCommand : public ICommand {
public:
    RightCommand() = default;

    ~RightCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;

    static std::unique_ptr<ICommand> create();

};

}
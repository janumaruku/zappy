/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TakeCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {

class TakeCommand : public ICommand {
public:
    TakeCommand() = default;

    ~TakeCommand() override = default;

    bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) override;

    bool execute(AISession &session,
        const std::vector<std::string> &cmd) override;

    static std::unique_ptr<ICommand> create();

};

}
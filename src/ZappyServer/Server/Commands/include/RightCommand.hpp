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
        const std::vector<std::string> &cmd,
        AISession &session) override;

    bool execute(const std::vector<std::string> &cmd,
        AISession &session) override;

    static std::unique_ptr<ICommand> create();

};

}
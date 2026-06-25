/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** MszCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class MszCommand : public GUIProtocolCommand {
public:
    MszCommand() = default;
    ~MszCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

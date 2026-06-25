/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SgtCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class SgtCommand : public GUIProtocolCommand {
public:
    SgtCommand() = default;
    ~SgtCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

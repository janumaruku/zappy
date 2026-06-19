/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PnwCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class PnwCommand : public GUIProtocolCommand {
public:
    PnwCommand() = default;
    ~PnwCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

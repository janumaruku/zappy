/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** PinCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class PinCommand : public GUIProtocolCommand {
public:
    PinCommand() = default;
    ~PinCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PdiCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class PdiCommand : public GUIProtocolCommand {
public:
    PdiCommand() = default;
    ~PdiCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

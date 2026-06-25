/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** EdiCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class EdiCommand : public GUIProtocolCommand {
public:
    EdiCommand() = default;
    ~EdiCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

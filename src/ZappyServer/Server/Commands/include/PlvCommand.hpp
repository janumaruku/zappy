/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PlvCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class PlvCommand : public GUIProtocolCommand {
public:
    PlvCommand() = default;
    ~PlvCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

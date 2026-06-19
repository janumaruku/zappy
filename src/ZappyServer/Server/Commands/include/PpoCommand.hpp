/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PpoCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class PpoCommand : public GUIProtocolCommand {
public:
    PpoCommand() = default;
    ~PpoCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

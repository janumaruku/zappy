/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** SstCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class SstCommand : public GUIProtocolCommand {
public:
    SstCommand() = default;
    ~SstCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

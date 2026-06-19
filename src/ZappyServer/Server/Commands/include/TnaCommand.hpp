/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** TnaCommand.hpp
*/

#pragma once

#include "GUIProtocolHandler.hpp"

namespace zappy::server {

class TnaCommand : public GUIProtocolCommand {
public:
    TnaCommand() = default;
    ~TnaCommand() override = default;

    bool operator()(GUISession &, const std::vector<std::string> &) override;
    bool execute(GUISession &, const std::vector<std::string> &) override;

    static std::unique_ptr<GUIProtocolCommand> create();
};

}

/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Commands
*/

#pragma once

#include <memory>
#include "WorldState.hpp"
#include "ProtocolHandler.hpp"

namespace zappy::gui {

class MszCommand: public ProtocolCommand {
public:
    ~MszCommand() override = default;

    bool execute(WorldState &, const std::vector<std::string> &) override;

    bool operator()(WorldState &, const std::vector<std::string> &) override;

    static std::unique_ptr<ProtocolCommand> create();
};

}
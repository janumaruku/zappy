/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MctCommand.hpp
*/


#pragma once

#include <memory>
#include "WorldState.hpp"
#include "ProtocolHandler.hpp"

namespace zappy::gui {

class MctCommand: public IGUICommand {
public:
    ~MctCommand() override = default;

    bool execute(WorldState &, const std::vector<std::string> &) override;

    bool operator()(WorldState &, const std::vector<std::string> &) override;

    static std::unique_ptr<IGUICommand> create();
};

}

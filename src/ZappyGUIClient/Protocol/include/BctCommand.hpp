/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BctCommand.hpp
*/

#pragma once

#include <memory>
#include "ICommand.hpp"
#include "ProtocolHandler.hpp"

namespace zappy::gui {

class BctCommand : public ProtocolCommand  {
public:
    ~BctCommand() override = default;

    bool execute(WorldState &, const std::vector<std::string> &) override;

    bool operator()(WorldState &, const std::vector<std::string> &) override;

    static std::unique_ptr<ProtocolCommand> create();
};

}

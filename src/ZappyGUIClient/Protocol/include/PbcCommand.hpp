/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PbcCommand.hpp
*/

#pragma once

#include <memory>
#include "ICommand.hpp"
#include "ProtocolHandler.hpp"

namespace zappy::gui {

class PbcCommand : public IGUICommand  {
public:
    ~PbcCommand() override = default;

    bool execute(WorldState &, const std::vector<std::string> &) override;

    bool operator()(WorldState &, const std::vector<std::string> &) override;

    static std::unique_ptr<IGUICommand> create();
};

}
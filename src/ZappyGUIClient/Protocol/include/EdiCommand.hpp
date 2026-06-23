/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EdiCommand.hpp
*/

#pragma once

#include <memory>
#include "ICommand.hpp"
#include "ProtocolHandler.hpp"

namespace zappy::gui {

class EdiCommand : public IGUICommand  {
public:
    ~EdiCommand() override = default;

    bool execute(WorldState &, const std::vector<std::string> &) override;

    bool operator()(WorldState &, const std::vector<std::string> &) override;

    static std::unique_ptr<IGUICommand> create();
};

}
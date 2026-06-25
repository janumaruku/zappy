/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** EboCommand.hpp
*/

#pragma once

#include <memory>
#include "ICommand.hpp"
#include "ProtocolHandler.hpp"

namespace zappy::gui {

class EboCommand : public IGUICommand  {
public:
    ~EboCommand() override = default;

    bool execute(WorldState &, const std::vector<std::string> &) override;

    bool operator()(WorldState &, const std::vector<std::string> &) override;

    static std::unique_ptr<IGUICommand> create();
};

}
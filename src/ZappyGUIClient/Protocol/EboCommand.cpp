/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** EboCommand.cpp
*/


#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "EboCommand.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

bool EboCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    uint id;

    if (cmd.empty()) {
        std::cerr << "EboCommand::" << __func__ << " No egg id provided" << std::endl;
        return false;
    }
    try {
        id = std::stoi(cmd[0]);
    } catch (const std::exception &e) {
        std::cerr << "EboCommand::" << __func__ << "Error Parsing egg id" << std::endl;
        return false;
    }
    s.onEggHatched(id);
    return true;
}

bool EboCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> EboCommand::create()
{
    return std::make_unique<EboCommand>(EboCommand());
}
}
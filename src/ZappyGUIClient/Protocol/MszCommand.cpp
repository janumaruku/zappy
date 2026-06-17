/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MszCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "MszCommand.hpp"

namespace zappy::gui {

bool MszCommand::execute(WorldState&, const std::vector<std::string>&)
{
    return true;
}

bool MszCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> MszCommand::create()
{
    return std::make_unique<MszCommand>(MszCommand());
}
}
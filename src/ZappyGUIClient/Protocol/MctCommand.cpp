/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MctCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "MctCommand.hpp"

namespace zappy::gui {

bool MctCommand::execute(WorldState&, const std::vector<std::string>&)
{
    return true;
}

bool MctCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> MctCommand::create()
{
    return std::make_unique<MctCommand>(MctCommand());
}
}
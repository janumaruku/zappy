/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BctCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "BctCommand.hpp"

namespace zappy::gui {

bool BctCommand::execute(WorldState&, const std::vector<std::string>&)
{
    return true;
}

bool BctCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> BctCommand::create()
{
    return std::make_unique<BctCommand>(BctCommand());
}
}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PpoCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "ProtocolHandler.hpp"
#include "PpoCommand.hpp"

namespace zappy::gui {

bool PpoCommand::execute(WorldState&, const std::vector<std::string>&)
{
    return true;
}

bool PpoCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PpoCommand::create()
{
    return std::make_unique<PpoCommand>(PpoCommand());
}
}
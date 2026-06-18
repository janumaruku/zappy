/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PpoCommand.cpp
*/


#include <memory>
#include <string>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "PpoCommand.hpp"

namespace zappy::gui {

bool PpoCommand::execute(WorldState &w, const std::vector<std::string>&cmd)
{
    const auto &id = cmd[1];
    data::Position pos(std::stoi(cmd[2]), std::stoi(cmd[3]));
    auto orientation = std::stoi(cmd[4]);

    w.onPlayerPosition(id, static_cast<data::Position>(pos),
    static_cast<data::Orientation>(orientation));
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
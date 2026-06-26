/*
** EPITECH PROJECT, 2026
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
    auto id = cmd[0];
    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());

    data::Position pos(std::stoi(cmd[1]), std::stoi(cmd[2]));
    auto orientation = std::stoi(cmd[3]) - 1;

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
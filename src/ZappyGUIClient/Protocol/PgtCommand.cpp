/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PgtCommand.cpp
*/


#include <cstdint>
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "GUIPlayer.hpp"
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "Tile.hpp"
#include "PgtCommand.hpp"

namespace zappy::gui {

bool PgtCommand::execute(WorldState& s, const std::vector<std::string> &cmd)
{
    auto id = cmd.at(0);

    if (!id.empty() && id.front() == '#')
        id.erase(id.begin());
    const auto &ressource = static_cast<data::Resource>(std::stoi(cmd.at(1)));
    s.onRessourceTaken(id, ressource);
    return true;
}

bool PgtCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PgtCommand::create()
{
    return std::make_unique<PgtCommand>(PgtCommand());
}
}
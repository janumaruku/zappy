/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PnwCommand.cpp
*/


#include <cstdint>
#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include "GUIPlayer.hpp"
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "PnwCommand.hpp"

namespace zappy::gui {

bool PnwCommand::execute(WorldState&s, const std::vector<std::string>&cmd)
{
    try {

        std::string id = cmd[0];
        if (!id.empty() && id.front() == '#')
            id.erase(id.begin());

        GUIPlayer player{id,
            cmd[5],
            {std::stoi(cmd[1]), std::stoi(cmd[2])},
            static_cast<data::Orientation>(std::stoi(cmd[3]) - 1),
            static_cast<uint8_t>(std::stoi(cmd[4]))};
    
        s.onPlayerNew(std::move(player));
    } catch(const std::exception &e) {
        return false;
    }
    return true;
}

bool PnwCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PnwCommand::create()
{
    return std::make_unique<PnwCommand>(PnwCommand());
}
}
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
        GUIPlayer player{cmd[1],
            cmd[6],
            {std::stoi(cmd[2]), std::stoi(cmd[3])},
            static_cast<data::Orientation>(std::stoi(cmd[4])),
            static_cast<uint8_t>(std::stoi(cmd[5]))};
    
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
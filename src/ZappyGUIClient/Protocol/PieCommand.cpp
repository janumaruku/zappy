/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** PieCommand.cpp
*/


#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "Position.hpp"
#include "ProtocolHandler.hpp"
#include "WorldState.hpp"
#include "PieCommand.hpp"

namespace zappy::gui {

bool PieCommand::execute(WorldState& s, const std::vector<std::string>&cmd)
{
    data::Position pos;
    int result;
    try {
        pos = data::Position(std::stoi(cmd[0]), std::stoi(cmd[1]));
        result = std::stoi(cmd[3]);
    } catch (const std::exception &e) {
        std::cerr << "PieCommand::" << __func__ << "Error Parsing position";
        return false;
    }
    s.onIncantationEnd(pos, result);
    return true;
}

bool PieCommand::operator()(WorldState& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<IGUICommand> PieCommand::create()
{
    return std::make_unique<PieCommand>(PieCommand());
}
}
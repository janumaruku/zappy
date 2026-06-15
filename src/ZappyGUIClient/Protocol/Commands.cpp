/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Commands.cpp
*/

#include "Commands.hpp"

#include <iostream>

namespace zappy::gui {
bool MszCommand::execute(WorldState &worldState,
    const std::vector<std::string> &args)
{
    try {
        worldState.onMapDimension(std::stoul(args[1]), std::stoul(args[2]));
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool MszCommand::operator()(WorldState &worldState,
    const std::vector<std::string> &args)
{
    return execute(worldState, args);
}

std::unique_ptr<GUICommand> MszCommand::create()
{
    return std::make_unique<MszCommand>();
}

/*
bool MctCommand::execute(WorldState &worldState, const std::vector<std::string> &args)
{
    try {
        worldState.
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}*/

}

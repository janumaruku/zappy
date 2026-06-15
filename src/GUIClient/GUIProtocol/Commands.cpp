/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Commands.cpp
*/

#include "Commands.hpp"

namespace zappy::gui {
bool MszCommand::execute(WorldState &worldState,
    const std::vector<std::string> &args)
{
    (void)worldState;
    (void)args;
    return false;
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

}

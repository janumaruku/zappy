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

bool BctCommand::execute(WorldState &worldState,
    const std::vector<std::string> &args)
{
    if (args.size() != 10)
        return false;
    try {
        const data::Position position(std::stoi(args[1]), std::stoi(args[2]));
        std::unordered_map<data::Resource, uint> resourcesList;

        for (auto i = 0; i < 7; ++i) {
            const auto amount = std::stoi(args[i + 3]);
            if (amount > 0)
                resourcesList[static_cast<data::Resource>(i)] = amount;
        }

        worldState.onTileContent(position, resourcesList);
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }
    return true;
}

bool BctCommand::operator()(WorldState &worldState,
    const std::vector<std::string> &args)
{
    return execute(worldState, args);
}

std::unique_ptr<GUICommand> BctCommand::create()
{
    return std::make_unique<BctCommand>();
}
}

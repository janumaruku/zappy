/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#ifndef ZAPPY_PROTOCOLHANDLER_HPP
#define ZAPPY_PROTOCOLHANDLER_HPP

#include <string>
#include "WorldState.hpp"
#include "FactoryTemplate.hpp"
#include "ICommand.hpp"
#include "IguiCommand.hpp"

namespace zappy::gui {
using GUICommand = ICommand<WorldState &, const std::vector<std::string> &>;
using CommandFactory = designPattern::FactoryTemplate<GUICommand, std::string>;

class ProtocolHandler {
public:
    explicit ProtocolHandler(WorldState &worldState) noexcept;

    static void handleLine(const std::string &line) noexcept;

    void registerCommand(
        ) noexcept;

private:
    WorldState &_worldState;
    CommandFactory _factory;

};
}
#endif

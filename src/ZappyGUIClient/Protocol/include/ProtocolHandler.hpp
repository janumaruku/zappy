/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#ifndef ZAPPY_PROTOCOLHANDLER_HPP
    #define ZAPPY_PROTOCOLHANDLER_HPP
    
#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include "FactoryTemplate.hpp"
#include "ICommand.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

using IGUICommand = ICommand<WorldState &, const std::vector<std::string> &>;

class ProtocolHandler {
public:
using CommandFactory = designPattern::FactoryTemplate<IGUICommand, std::string>;

    ProtocolHandler() = delete;
    ProtocolHandler(WorldState &) noexcept;

    void handleLine(const std::string &line) noexcept;

    
private:
    void registerCommands() noexcept;

    WorldState& _worldState;
    CommandFactory _factory;
};

}
#endif
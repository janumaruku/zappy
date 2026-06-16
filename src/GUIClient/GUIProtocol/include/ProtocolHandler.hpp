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
#include "MctCommand.hpp"
#include "BctCommand.hpp"
#include "MszCommand.hpp"

namespace zappy::gui {

class ProtocolHandler {
public:
using ProtocolCommand = ICommand<WorldState &, std::vector<std::string>>;
using CommandFactory = designPattern::FactoryTemplate<ProtocolCommand, std::string>;

    ProtocolHandler() noexcept;

    void handleLine(const std::string &line) noexcept;

    template<typename T>
    void registerCommand(const std::string &name) noexcept;

private:
    WorldState& _worldState;
    CommandFactory _factory;
};

}
#endif

#include "ProtocolHandler.tpp"
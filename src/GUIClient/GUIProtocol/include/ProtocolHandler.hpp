/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#ifndef ZAPPY_PROTOCOLHANDLER_HPP
    #define ZAPPY_PROTOCOLHANDLER_HPP
    #include <string>
    #include "ICommand.hpp"
    #include "WorldState.hpp"
    #include "FactoryTemplate.hpp"

class ProtocolHandler {
public:
    using CommandFactory = FactoryTemplate<ICommand,std::string, WorldState&,
        const std::vector<std::string> &>
    ProtocolHandler(WorldState& worldState) noexcept = default;

    void handleLine(const std::string line) noexcept;

private:
    WorldState& _worldState;
    CommandFactory _factory;

};
#endif

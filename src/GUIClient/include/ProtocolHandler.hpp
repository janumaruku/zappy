/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#ifndef ZAPPY_PROTOCOLHANDLER_HPP
    #define ZAPPY_PROTOCOLHANDLER_HPP
    #include <map>
    #include <string>
    #include <functional>
    #include "ICommand.hpp"

class ProtocolHandler {
    private:
        WorldState& _worldState;

        ProtocolHandler() noexcept;
        std::map<std::string, std::function<ICommand*()>> _factories;
        void handleLine(const std::string line) noexcept;
        void registerCommand(const std::string &name,
            std::function<ICommand*()> creator) noexcept;
};
#endif

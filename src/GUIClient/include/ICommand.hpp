/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ICommand
*/

#ifndef ZAPPY_ICOMMAND_HPP
    #define ZAPPY_ICOMMAND_HPP
    #include <list>
    #include <string>

class ICommand {
    private:
        virtual void execute(WorldState& worldState, const std::list<std::string>& args) = 0;
};
#endif

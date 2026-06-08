/*
** Created by darkcrossprime, 06/06/2026.
** zappy
** File Description:
** Core.hpp
*/

#pragma once

#include "Shell.hpp"

class Core {
public:
    Core(int argc, char** argv);
    void run();

private:
    int _argc;
    std::vector<std::string> _argv;

    int _port = 0;
    uint _width = 0;
    uint _height = 0;
    std::vector<std::string> _teams;
    uint _clientPerTeam = 0;
    uint _frequency = 0;

    shell::command::CommandDefinition _serverCommands;
    void buildServerCommands();
};

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
    explicit Core(char** argv);
    void run();

private:
    std::vector<std::string> _argv;

    int _port = 0;
    int _width = 0;
    int _height = 0;
    std::vector<std::string> _teams;
    uint _clientPerTeam = 0;
    uint _frequency = 1;

    shell::command::CommandDefinition _serverCommands;
    void buildServerCommands();
};

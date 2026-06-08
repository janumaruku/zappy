/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Core.hpp
*/


#ifndef CORE_HPP_
    #define CORE_HPP_
#include "../../../Network/include/IoContext.hpp"
#include "CommandDefinition.hpp"

namespace GUI {
    class Core {
        public:
            Core(int argc, char **argv);
            void run();
        private:
            int _argc;
            std::vector<std::string> _argv;

            int _port = 0;
            std::string _machine;
            network::IOContext _ioc;
            //TCPClient _tcpClient;
            //WorldState _worldState;
            //Renderer _renderer;
            shell::command::CommandDefinition _GUICommands;

            void buildGUICommands();
    };
}

#endif

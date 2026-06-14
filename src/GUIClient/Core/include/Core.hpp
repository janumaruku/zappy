/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Core.hpp
*/

#ifndef CORE_HPP
#define CORE_HPP
#include <memory>

#include "CommandDefinition.hpp"
#include "IoContext.hpp"
#include "TCPClient.hpp"
#include "WorldState.hpp"

namespace zappy::gui {
class Core {
public:
    explicit Core(char **argv);
    void run();

private:
    std::vector<std::string> _argv;

    network::IOContext _ioc;
    std::unique_ptr<TCPClient> _tcpClient;
    WorldState _worldState;
    // Renderer _renderer;
    shell::command::CommandDefinition _guiCommands;

    void buildGUICommands();
};
} // namespace zappy::gui

#endif

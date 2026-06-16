/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AIProtocolHandler.cpp
*/

#include "AIProtocolHandler.hpp"
#include <string>
#include <unordered_map>
#include <vector>
#include <exception>
#include "AISession.hpp"
#include "AISessionCommands.hpp"

namespace zappy::server {

AIProtocolHandler::AIProtocolHandler()
{
    _factory.registerCreator<BroadcastCommand>("Broadcast");
    _availableCommands.emplace_back("Broadcast");
    _factory.registerCreator<ConnectNbrCommand>("Connect_nbr");
    _availableCommands.emplace_back("Connect_nbr");
    _factory.registerCreator<EjectCommand>("Eject");
    _availableCommands.emplace_back("Eject");
    _factory.registerCreator<ForkCommand>("Fork");
    _availableCommands.emplace_back("Fork");
    _factory.registerCreator<ForwardCommand>("Forward");
    _availableCommands.emplace_back("Forward");
    _factory.registerCreator<IncantationCommand>("Incantation");
    _availableCommands.emplace_back("Incantation");
    _factory.registerCreator<InventoryCommand>("Inventory");
    _availableCommands.emplace_back("Inventory");
    _factory.registerCreator<LeftCommand>("Left");
    _availableCommands.emplace_back("Left");
    _factory.registerCreator<LookCommand>("Look");
    _availableCommands.emplace_back("Look");
    _factory.registerCreator<RightCommand>("Right");
    _availableCommands.emplace_back("Right");
    _factory.registerCreator<SetCommand>("Set");
    _availableCommands.emplace_back("Set");
    _factory.registerCreator<TakeCommand>("Take");
    _availableCommands.emplace_back("Take");
}

const std::vector<std::string> &AIProtocolHandler::getAvailableCommands() const
{
    return _availableCommands;
}

void AIProtocolHandler::handleLine(const std::vector<std::string> &cmd, AISession &session)
{
    auto toExec = _factory.create(cmd[0]);
    try {
        toExec->execute(cmd, session);
    } catch (const std::exception &e) {
        session.send(COMMAND_NOT_FOUND);
    }
}

}
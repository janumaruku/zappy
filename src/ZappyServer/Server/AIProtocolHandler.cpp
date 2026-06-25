/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** AIProtocolHandler.cpp
*/

#include "AIProtocolHandler.hpp"
#include <string>
#include <vector>
#include <exception>
#include "AISession.hpp"
#include "AISessionCommands.hpp"

namespace zappy::server {

AIProtocolHandler::AIProtocolHandler()
{
    registerCreators();
}

void AIProtocolHandler::registerCreators() noexcept
{
    _factory.registerCreator<BroadcastCommand>("Broadcast");
    _factory.registerCreator<ConnectNbrCommand>("Connect_nbr");
    _factory.registerCreator<EjectCommand>("Eject");
    _factory.registerCreator<ForkCommand>("Fork");
    _factory.registerCreator<ForwardCommand>("Forward");
    _factory.registerCreator<IncantationCommand>("Incantation");
    _factory.registerCreator<InventoryCommand>("Inventory");
    _factory.registerCreator<LeftCommand>("Left");
    _factory.registerCreator<LookCommand>("Look");
    _factory.registerCreator<RightCommand>("Right");
    _factory.registerCreator<SetCommand>("Set");
    _factory.registerCreator<TakeCommand>("Take");
}

AIProtocolHandler::~AIProtocolHandler() = default;

void AIProtocolHandler::handleLine(const std::vector<std::string> &cmd, AISession &session)
{
    try {
        auto toExec = _factory.create(cmd[0]);
        toExec->execute(session, cmd);
    } catch (const std::exception &e) {
        session.send(COMMAND_NOT_FOUND);
    }
}

const AICommandFactory &AIProtocolHandler::getFactory() const
{
    return _factory;
} 

}
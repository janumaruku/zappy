/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AIProtocolHandler.cpp
*/

#include "AIProtocolHandler.hpp"
#include "AISessionCommands.hpp"

namespace zappy::server {

AIProtocolHandler::AIProtocolHandler() {
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

}
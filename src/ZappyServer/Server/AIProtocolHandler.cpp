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
    registerCreator<BroadcastCommand<AISession, std::vector<std::string>>>("Broadcast");
    _availableCommands.emplace_back("Broadcast");
    registerCreator<ConnectNbrCommand<AISession, std::vector<std::string>>>("Connect_nbr");
    _availableCommands.emplace_back("Connect_nbr");
    registerCreator<EjectCommand<AISession, std::vector<std::string>>>("Eject");
    _availableCommands.emplace_back("Eject");
    registerCreator<ForkCommand<AISession, std::vector<std::string>>>("Fork");
    _availableCommands.emplace_back("Fork");
    registerCreator<ForwardCommand<AISession, std::vector<std::string>>>("Forward");
    _availableCommands.emplace_back("Forward");
    registerCreator<IncantationCommand<AISession, std::vector<std::string>>>("Incantation");
    _availableCommands.emplace_back("Incantation");
    registerCreator<InventoryCommand<AISession, std::vector<std::string>>>("Inventory");
    _availableCommands.emplace_back("Inventory");
    registerCreator<LeftCommand<AISession, std::vector<std::string>>>("Left");
    _availableCommands.emplace_back("Left");
    registerCreator<LookCommand<AISession, std::vector<std::string>>>("Look");
    _availableCommands.emplace_back("Look");
    registerCreator<RightCommand<AISession, std::vector<std::string>>>("Right");
    _availableCommands.emplace_back("Right");
    registerCreator<SetCommand<AISession, std::vector<std::string>>>("Set");
    _availableCommands.emplace_back("Set");
    registerCreator<TakeCommand<AISession, std::vector<std::string>>>("Take");
    _availableCommands.emplace_back("Take");
}

AIProtocolHandler::~AIProtocolHandler() = default;

const std::vector<std::string> &AIProtocolHandler::getAvailableCommands() const noexcept
{
    return _availableCommands;
}

void AIProtocolHandler::handleLine(const std::vector<std::string> &cmd, AISession &session)
{
    auto toExec = _factory.create(cmd[0]);
    try {
        toExec->execute(session, cmd);
    } catch (const std::exception &e) {
        session.send(COMMAND_NOT_FOUND);
    }
}

}
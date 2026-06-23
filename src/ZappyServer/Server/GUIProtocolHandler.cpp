/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** GUIProtocolHandler.cpp
*/

#include "GUIProtocolHandler.hpp"
#include "GUISession.hpp"

#include <exception>

#include "MszCommand.hpp"
#include "PinCommand.hpp"
#include "PnwCommand.hpp"
#include "PpoCommand.hpp"
#include "TnaCommand.hpp"

namespace zappy::server {

GUIProtocolHandler::GUIProtocolHandler()
{
    registerCreators();
}

GUIProtocolHandler::~GUIProtocolHandler() = default;

void GUIProtocolHandler::registerCreators() noexcept
{
    _factory.registerCreator<MszCommand>("msz");
    _factory.registerCreator<PinCommand>("pin");
    _factory.registerCreator<PnwCommand>("pnw");
    _factory.registerCreator<PpoCommand>("ppo");
    _factory.registerCreator<TnaCommand>("tna");
}

bool GUIProtocolHandler::handleLine(const std::string &command, GUISession &session,
    const std::vector<std::string> &args)
{
    try {
        auto toExec = _factory.create(command);
        return toExec->execute(session, args);
    } catch (const std::exception &) {
        session.send("suc\n");
        return false;
    }
}

}

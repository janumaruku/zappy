/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** GUIProtocolHandler.cpp
*/

#include "GUIProtocolHandler.hpp"

#include <exception>

#include "AISession.hpp"
#include "EdiCommand.hpp"
#include "GUISession.hpp"
#include "MszCommand.hpp"
#include "PinCommand.hpp"
#include "PlvCommand.hpp"
#include "PnwCommand.hpp"
#include "PpoCommand.hpp"
#include "SgtCommand.hpp"
#include "SstCommand.hpp"
#include "TnaCommand.hpp"

namespace zappy::server {

GUIProtocolHandler::GUIProtocolHandler()
{
    registerCreators();
}

GUIProtocolHandler::~GUIProtocolHandler() = default;

void GUIProtocolHandler::registerCreators() noexcept
{
    _factory.registerCreator<EdiCommand>("edi");
    _factory.registerCreator<MszCommand>("msz");
    _factory.registerCreator<PinCommand>("pin");
    _factory.registerCreator<PnwCommand>("pnw");
    _factory.registerCreator<PlvCommand>("plv");
    _factory.registerCreator<PpoCommand>("ppo");
    _factory.registerCreator<SgtCommand>("sgt");
    _factory.registerCreator<SstCommand>("sst");
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

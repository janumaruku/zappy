/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ProtocolHandler
*/

#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include "EboCommand.hpp"
#include "EdiCommand.hpp"
#include "PbcCommand.hpp"
#include "PdiCommand.hpp"
#include "PdrCommand.hpp"
#include "PexCommand.hpp"
#include "PfkCommand.hpp"
#include "PgtCommand.hpp"
#include "PicCommand.hpp"
#include "PieCommand.hpp"
#include "PinCommand.hpp"
#include "PlvCommand.hpp"
#include "PnwCommand.hpp"
#include "PpoCommand.hpp"
#include "SegCommand.hpp"
#include "SgtCommand.hpp"
#include "SmgCommand.hpp"
#include "SstCommand.hpp"
#include "StringUtils.hpp"
#include "ProtocolHandler.hpp"
#include "BctCommand.hpp"
#include "MctCommand.hpp"
#include "MszCommand.hpp"
#include "EnwCommand.hpp"
#include "TnaCommand.hpp"
#include "WorldState.hpp"

namespace zappy::gui {

ProtocolHandler::ProtocolHandler(WorldState &w) noexcept :
_worldState(w)
{
    registerCommands();
}

void ProtocolHandler::registerCommands() noexcept
{
    _factory.registerCreator<BctCommand>("bct");
    _factory.registerCreator<EboCommand>("ebo");
    _factory.registerCreator<EdiCommand>("edi");
    _factory.registerCreator<EnwCommand>("enw");
    _factory.registerCreator<MctCommand>("mct");
    _factory.registerCreator<MszCommand>("msz");
    _factory.registerCreator<PbcCommand>("pbc");
    _factory.registerCreator<PdiCommand>("pdi");
    _factory.registerCreator<PdrCommand>("pdr");
    _factory.registerCreator<PexCommand>("pex");
    _factory.registerCreator<PfkCommand>("pfk");
    _factory.registerCreator<PgtCommand>("pgt");
    _factory.registerCreator<PicCommand>("pic");
    _factory.registerCreator<PieCommand>("pie");
    _factory.registerCreator<PinCommand>("pin");
    _factory.registerCreator<PlvCommand>("plv");
    _factory.registerCreator<PnwCommand>("pnw");
    _factory.registerCreator<PpoCommand>("ppo");
    _factory.registerCreator<SegCommand>("seg");
    _factory.registerCreator<SgtCommand>("sgt");
    _factory.registerCreator<SmgCommand>("smg");
    _factory.registerCreator<SstCommand>("sst");
    _factory.registerCreator<TnaCommand>("tna");
}

void ProtocolHandler::handleLine(const std::string& line) noexcept
{
    auto cmd = utils::StringUtils::split(line);
    
    try {
        auto name = cmd[0];
        cmd.erase(cmd.begin());
        auto toExec = _factory.create(name);
        toExec->execute(_worldState, cmd);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr.flush();
    }
}

}

/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** EdiCommand.cpp
*/

#include "EdiCommand.hpp"

#include <charconv>
#include <format>
#include <memory>
#include <string>
#include <system_error>

#include "GUISession.hpp"
#include "Server.hpp"

namespace zappy::server {

static std::string protocolEggId(const std::string &arg)
{
    if (!arg.empty() && arg.front() == '#')
        return arg.substr(1);
    return arg;
}

static bool parseEggId(const std::string &value, uint &eggId)
{
    uint parsed = 0;
    const auto *begin = value.data();
    const auto *end = begin + value.size();
    const auto result = std::from_chars(begin, end, parsed);

    if (result.ec != std::errc() || result.ptr != end || parsed == 0)
        return false;
    eggId = parsed;
    return true;
}

bool EdiCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    uint eggId = 0;

    if (args.size() != 1 || !parseEggId(protocolEggId(args[0]), eggId)) {
        session.send("sbp\n");
        return false;
    }

    auto &map = session.getServer().getMap();

    if (!map.getEggs().contains(eggId)) {
        session.send("suc\n");
        return false;
    }

    map.removeEgg(eggId);
    session.getServer().notifyGUI(std::format("edi #{}\n", eggId));
    return true;
}

bool EdiCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> EdiCommand::create()
{
    return std::make_unique<EdiCommand>();
}

}

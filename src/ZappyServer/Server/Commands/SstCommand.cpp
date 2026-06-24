/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** SstCommand.cpp
*/

#include "SstCommand.hpp"

#include <charconv>
#include <memory>
#include <string>
#include <system_error>

#include "GUISession.hpp"
#include "Server.hpp"

namespace zappy::server {

static bool parseFrequency(const std::string &value, uint &frequency)
{
    uint parsed = 0;
    const auto *begin = value.data();
    const auto *end = begin + value.size();
    const auto result = std::from_chars(begin, end, parsed);

    if (result.ec != std::errc() || result.ptr != end || parsed == 0)
        return false;
    frequency = parsed;
    return true;
}

bool SstCommand::execute(GUISession &session, const std::vector<std::string> &args)
{
    uint frequency = 0;

    if (args.size() != 1 || !parseFrequency(args[0], frequency)) {
        session.send("sbp\n");
        return false;
    }

    session.getServer().setFrequency(frequency);
    session.getServer().notifyGUI("sst " + std::to_string(frequency) + "\n");
    return true;
}

bool SstCommand::operator()(GUISession &session, const std::vector<std::string> &args)
{
    return execute(session, args);
}

std::unique_ptr<GUIProtocolCommand> SstCommand::create()
{
    return std::make_unique<SstCommand>();
}

}

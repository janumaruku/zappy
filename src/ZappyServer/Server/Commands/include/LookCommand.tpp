/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** LookCommandCommand.cpp
*/

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "LookCommandCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool LookCommandCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool LookCommandCommand::execute(const std::vector<std::string> &cmd, AISession &session)
{
    std::string message;
    std::size_t messageWords = cmd.size() - 1;

    for (std::size_t i = 0; i != messageWords; i++) {
        message.append(cmd[i]);
        if (i < messageWords)
            message.append(" ");
    }
    session.send("LookCommand" + message + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> LookCommandCommand::create()
{
    return std::make_unique<LookCommandCommand>(LookCommandCommand());
}

}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ConnectNbrCommandCommand.cpp
*/

#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "ICommand.hpp"
#include "Server.hpp"
#include "ConnectNbrCommandCommand.hpp"
#include "AISession.hpp"
#include "ZappyConstants.hpp"

namespace zappy::server {

bool ConnectNbrCommandCommand::operator()(const std::vector<std::string> &cmd, AISession &session)
{
    return execute(cmd, session);
}

bool ConnectNbrCommandCommand::execute(const std::vector<std::string> &cmd, AISession &session)
{
    std::string message;
    std::size_t messageWords = cmd.size() - 1;

    for (std::size_t i = 0; i != messageWords; i++) {
        message.append(cmd[i]);
        if (i < messageWords)
            message.append(" ");
    }
    session.send("ConnectNbrCommand" + message + zappy::data::PACKET_END);
    return true;
}

std::unique_ptr<ICommand> ConnectNbrCommandCommand::create()
{
    return std::make_unique<ConnectNbrCommandCommand>(ConnectNbrCommandCommand());
}

}
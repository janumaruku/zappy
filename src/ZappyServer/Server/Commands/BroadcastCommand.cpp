/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** BroadcastCommand.cpp
*/



#include <memory>
#include <string>
#include <vector>
#include "AIProtocolHandler.hpp"
#include "AISession.hpp"
#include "BroadcastCommand.hpp"

namespace zappy::server {

bool BroadcastCommand::execute(AISession& s, const std::vector<std::string>& v)
{
    std::string data;
    std::size_t words = v.size();

    for (std::size_t i = 1; i != words; i++) {
        data.append(v[i]);
        if (i < words)
            data.append(" ");
    }
    s.send(data);
    return true;
}

bool BroadcastCommand::operator()(AISession& s, const std::vector<std::string>& v)
{
    return execute(s, v);
}

std::unique_ptr<AIProtocolCommand> BroadcastCommand::create()
{
    return std::make_unique<BroadcastCommand>(BroadcastCommand());
}

}
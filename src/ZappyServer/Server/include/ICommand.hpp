/*
** EPITECH PROJECT, 2026
**
** File description:
**
*/

#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <vector>
#include <string>
#include "Server.hpp"

namespace zappy::server {

class IShellCommand {
public:
    IShellCommand() = default;

    virtual ~IShellCommand() = default;

    virtual bool operator()(
        AISession &session,
        std::vector<std::string> cmd) = 0;

    virtual bool execute(AISession &session,
        std::vector<std::string> cmd) = 0;
};

}
#endif // !ICOMMAND_HPP

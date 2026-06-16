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

class ICommand {
public:
    ICommand() = default;

    virtual ~ICommand() = default;

    virtual bool operator()(
        AISession &session,
        const std::vector<std::string> &cmd) = 0;

    virtual bool execute(AISession &session,
        const std::vector<std::string> &cmd) = 0;
};

}
#endif // !ICOMMAND_HPP

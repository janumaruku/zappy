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
        const std::vector<std::string> &cmd,
        AISession &session) = 0;

    virtual bool execute(const std::vector<std::string> &cmd,
        AISession &session) = 0;
};

}
#endif // !ICOMMAND_HPP

/*
** EPITECH PROJECT, 2026
**
** File description:
**
*/

#ifndef ICOMMAND_HPP
#define ICOMMAND_HPP

#include <memory>

namespace zappy::server {

template <typename... Args>
class ICommand {
public:
    virtual ~ICommand() = 0;

    virtual bool execute(AISession& s, const std::vector<std::string>& v) = 0;

    virtual bool operator()(AISession& s, const std::vector<std::string>& v) = 0;
};


}
#endif // !ICOMMAND_HPP

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
    virtual ~ICommand() = default;

    virtual bool execute(Args... args) = 0;

    virtual bool operator()(Args... args) = 0;
};


}
#endif // !ICOMMAND_HPP

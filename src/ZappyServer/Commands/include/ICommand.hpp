/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ICommand interface for server commands
*/

#ifndef ICOMMAND_HPP_
#define ICOMMAND_HPP_

#include <memory>
#include <string>

namespace zappy::server {
class AISession;
class Server;

class ICommand {
public:
    virtual ~ICommand() = default;

    virtual void execute(AISession &session, Server &server, const std::string &args) = 0;

    virtual std::string name() const { return {}; }
};

using ICommandPtr = std::unique_ptr<ICommand>;

} // namespace zappy::server

#endif // ICOMMAND_HPP_

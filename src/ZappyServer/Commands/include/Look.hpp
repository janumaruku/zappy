/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Look command header
*/

#ifndef LOOK_HPP_
#define LOOK_HPP_

#include <memory>
#include <string>

#include "ICommand.hpp"

namespace zappy::server {

class Look : public ICommand {
public:
    Look() = default;
    ~Look() override = default;

    void execute(AISession &session, Server &server, const std::string &args) override;

    static std::unique_ptr<ICommand> create();

    static std::string commandName() { return "Look"; }
};

} // namespace zappy::server

#endif 
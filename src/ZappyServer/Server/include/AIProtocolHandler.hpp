/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AIProtocolHandler.hpp
*/

#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include "AISession.hpp"
#include "FactoryTemplate.hpp"
#include "ICommand.hpp"
#include "Server.hpp"

namespace zappy::server {

using AICommandFactory = designPattern::FactoryTemplate<ICommand, std::string>;
class AIProtocolHandler {
public:

    explicit AIProtocolHandler();

    ~AIProtocolHandler();

    void handleLine(const std::vector<std::string>&, AISession &);

    const std::vector<std::string> &getAvailableCommands() const;

private:
    AICommandFactory _factory;
    std::vector<std::string> _availableCommands;
};
}
/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AIProtocolHandler.hpp
*/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "FactoryTemplate.hpp"
#include "ForwardCommand.hpp"
#include "ICommand.hpp"
#include "Server.hpp"

namespace zappy::server {

class AIProtocolHandler {
public:
using AICommandFactory = designPattern::FactoryTemplate<ICommand, std::string>;

    AIProtocolHandler();
    ~AIProtocolHandler();

    void handleLine(const std::vector<std::string>&, AISession &);

private:
    AICommandFactory _factory;
};

}
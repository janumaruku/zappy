/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** GUIProtocolHandler.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "FactoryTemplate.hpp"
#include "ICommand.hpp"

namespace zappy::server {

class GUISession;

using GUIProtocolCommand = ICommand<GUISession&, const std::vector<std::string>&>;
using GUICommandFactory = designPattern::FactoryTemplate<GUIProtocolCommand, std::string>;

class GUIProtocolHandler {
public:
    GUIProtocolHandler();
    ~GUIProtocolHandler();

    bool handleLine(const std::string &command, GUISession &session,
        const std::vector<std::string> &args = {});

private:
    void registerCreators() noexcept;

    GUICommandFactory _factory;
};

}

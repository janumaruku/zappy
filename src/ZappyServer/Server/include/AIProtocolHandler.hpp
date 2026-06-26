/*
** EPITECH PROJECT, 2026
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

using AIProtocolCommand = ICommand<AISession&, const std::vector<std::string>&>;
using AICommandFactory = designPattern::FactoryTemplate<AIProtocolCommand, std::string>;

class AIProtocolHandler {
public:

    explicit AIProtocolHandler();

    ~AIProtocolHandler();

    void handleLine(const std::vector<std::string>&, AISession &);

    [[nodiscard]] const AICommandFactory &getFactory() const;

private:
    void registerCreators() noexcept;
    AICommandFactory _factory;
};
}
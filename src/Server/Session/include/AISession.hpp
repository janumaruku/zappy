/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef AISESSION_HPP_
    #define AISESSION_HPP_

    #include <cstddef>
#include <string>
#include "IClientSession.hpp"
    #include "Temp.hpp"

namespace zappy::server {

constexpr char END_OF_TRANSMISSION = '\n';

class AISession : public IClientSession {
public:
    AISession() = delete;
    ~AISession() override = default;

    void start() override;
    void handleTransmission() override;

    [[nodiscard]] static std::size_t getResultSize(const std::string &str);
    [[nodiscard]] static std::vector<std::string> sanitizedSplit(const std::string &str);

private:


    Server &_server;
    Player _player;
    uint _pending_commands;
    SteadyTimer _command_timer;
    SteadyTimer _starvation_timer;
};

}

#endif

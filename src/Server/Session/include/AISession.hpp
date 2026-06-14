/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef AISESSION_HPP_
    #define AISESSION_HPP_

#include <cstddef>
#include <queue>
#include <string>
#include <vector>
#include "IClientSession.hpp"
#include "Timer.hpp"
#include "Player.hpp"

namespace zappy::server {

// remove this when possible
class Server;

// placeholder
constexpr uint COMMAND_TRIGGER_DIVISOR = 1;
constexpr uint RESPONSE_TIME = 1;
constexpr std::string PLACEHOLDER_SERVER_RESPONSE = "Welcome !";
//

constexpr uint MAX_PENDING_COMMANDS = 10;

constexpr char END_OF_TRANSMISSION = '\n';

class AISession : public IClientSession {
public:

    AISession() = delete;
    ~AISession() override = default;

    void start() override;
    void handleTransmission() override;

    [[nodiscard]] const Player &getPlayer() const noexcept;
    [[nodiscard]] const Server &getServer() const noexcept;

    [[nodiscard]] static std::size_t getResultSize(const std::string &str);
    [[nodiscard]] static std::vector<std::string> sanitizedSplit(const std::string &str);


    void scheduleResponse(const uint &durationConstant, const std::string &response);

private:

    void onCommandComplete();

    Server &_server;
    Player _player;
    SteadyTimer _command_timer;
    SteadyTimer _starvation_timer;
    
    uint _pending_commands = 0;
    std::queue<std::vector<std::string>> _commandQueue;
};

}

#endif

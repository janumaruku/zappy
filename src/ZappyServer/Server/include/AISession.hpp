/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef AISESSION_HPP_
    #define AISESSION_HPP_

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include "AClientSession.hpp"
#include "AIProtocolHandler.hpp"
#include "ConnectedSocket.hpp"
#include "Timer.hpp"
#include "Player.hpp"
#include "Server.hpp"

namespace zappy::server {

// placeholder
constexpr uint COMMAND_TRIGGER_DIVISOR = 1;
constexpr uint RESPONSE_TIME = 1;
constexpr std::string PLACEHOLDER_SERVER_RESPONSE = "Welcome !";
//

constexpr std::string COMMAND_NOT_FOUND = "ko\n";

constexpr uint MAX_PENDING_COMMANDS = 10;

class AISession : public AClientSession {
public:

    AISession() = delete;
    explicit AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
        Server &server, Player &player);
    ~AISession() override = default;

    void handleTransmission() override;

    [[nodiscard]] const Player &getPlayer() const noexcept;
    [[nodiscard]] const Server &getServer() const noexcept;

    void scheduleResponse(const uint &durationConstant, const std::string &response);

private:

    void onCommandComplete();
    void executeNext();

    Server &_server;
    Player &_player;
    SteadyTimer _command_timer;
    SteadyTimer _starvation_timer;
    
    uint _pending_commands = 0;
    std::queue<std::vector<std::string>> _commandQueue;

    AIProtocolHandler _protocolHandler;

};

}

#endif
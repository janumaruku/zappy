/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>
#include "AClientSession.hpp"
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


class AIProtocolHandler;

class AISession : public AClientSession {
public:

    AISession() = delete;
    explicit AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
        Server &server, Player &player);
    ~AISession() override;

    void handleTransmission() override;

    [[nodiscard]] const Player &getPlayer() const noexcept;
    [[nodiscard]] Player &getPlayer() noexcept;
    [[nodiscard]] const Server &getServer() const noexcept;
    [[nodiscard]] Server &getServer() noexcept;

    void scheduleResponse(const uint &durationConstant, const std::string &response);

    void freeze() noexcept;
    void unfreeze() noexcept;
    [[nodiscard]] bool isFrozen() const noexcept;

    void scheduleTask(const uint &durationConstant,
        const std::function<void()> &task);

private:

    void onCommandComplete();
    void executeNext();

    Server &_server;
    Player &_player;
    SteadyTimer _command_timer;
    SteadyTimer _starvation_timer;
    
    uint _pending_commands = 0;
    std::queue<std::vector<std::string>> _commandQueue;

    bool _frozen = false;

    std::unique_ptr<AIProtocolHandler> _protocolHandler;

};

}

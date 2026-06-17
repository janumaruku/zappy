/*
** EPITECH PROJECT, 2026
** Main
** File description:
** main
*/

#include "AISession.hpp"

#include <thread>
#include <chrono>
#include <memory>

namespace zappy::server {

AISession::AISession(const std::shared_ptr<network::ConnectedSocket> &socket,
    Server &server, Player &player): AClientSession{socket}, _server{server},
    _player{player}
{
    (void)_pending_commands;
}

void AISession::scheduleResponse(int delay, const std::string &response)
{
    auto msg = std::make_shared<std::string>(response);

    const auto ms = std::chrono::milliseconds(static_cast<long long>(delay) * 100LL);

    std::thread([this, msg, ms]() {
        std::this_thread::sleep_for(ms);

        std::string toSend = *msg;
        AClientSession::send(toSend);
    }).detach();
}

void AISession::handleTransmission()
{
    // !todo(call protocol handler here)
}

} // namespace zappy::server

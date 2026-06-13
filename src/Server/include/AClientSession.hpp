/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef ACLIENTSESSION_HPP_
    #define ACLIENTSESSION_HPP_

    #include <string>
    #include "IClientSession.hpp"

namespace zappy::server {

class AClientSession : public IClientSession {
public:
    AClientSession() = delete;
    ~AClientSession() override = default;

    void start() override;
    void send(std::string &data) override;
    std::string receive() override;
    

protected:
    void handleRead() override;
    void handleWrite() override;
};

}

#endif

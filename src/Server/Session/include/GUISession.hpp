/*
** EPITECH PROJECT, 2026
** Header
** File description:
** New header
*/

#ifndef GUISESSION_HPP_
    #define GUISESSION_HPP_

    #include "IClientSession.hpp"

namespace zappy::server {

class GUISession : public IClientSession {
public:
    GUISession();
    ~GUISession() override = default;

    void start() override;

protected:
    void handleTransmission() override;
};

}

#endif

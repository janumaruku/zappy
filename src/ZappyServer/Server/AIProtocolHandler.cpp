/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AIProtocolHandler.cpp
*/

#include "AIProtocolHandler.hpp"

namespace zappy::server {

AIProtocolHandler::AIProtocolHandler() {
    _factory.registerCreator<typename ConcreteClass>(std::basic_string<char> key)
}

}
/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** AIClientSession.tpp
*/

#pragma once

#include "AIProtocolHandler.hpp"

namespace zappy::server {

template <typename T>
void AIProtocolHandler::registerCreator(const std::string &name) noexcept
{
    _factory.registerCreator<T>(name);
}

}
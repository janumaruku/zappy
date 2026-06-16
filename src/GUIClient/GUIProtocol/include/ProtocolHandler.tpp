/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ProtocolHandler.tpp
*/

#pragma once

#include "ProtocolHandler.hpp"

namespace zappy::gui {

template<typename T>
void ProtocolHandler::registerCommand(const std::string &name) noexcept
{
    _factory.registerCreator<T>(name);
}

}
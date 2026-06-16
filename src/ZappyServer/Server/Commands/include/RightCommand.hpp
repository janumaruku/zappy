/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** RightCommandCommand.hpp
*/

#pragma once

#include "ICommand.hpp"

namespace zappy::server {
template<typename... Args>
class RightCommandCommand : public ICommand<Args...> {
public:
    RightCommandCommand() = default;

    ~RightCommandCommand() override = default;

    bool operator()(Args... args) override;

    bool execute(Args... args) override;

    static std::unique_ptr<ICommand<Args...>> create();

};

}
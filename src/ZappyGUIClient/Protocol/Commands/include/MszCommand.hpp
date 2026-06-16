/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** Commands
*/

#pragma once

#include <memory>
#include "WorldState.hpp"
#include "ICommand.hpp"

namespace zappy::gui {

template <typename...Args>
class MszCommand: public ICommand<Args...> {
public:
    virtual ~MszCommand() = default;

    bool execute(Args...args) override;

    bool operator()(Args...args) override;

    static std::unique_ptr<ICommand<Args...>> create();
};

}

#include "MszCommand.tpp"
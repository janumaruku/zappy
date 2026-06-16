/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** MctCommand.hpp
*/


#pragma once

#include <memory>
#include "WorldState.hpp"
#include "ICommand.hpp"

namespace zappy::gui {

template <typename...Args>
class MctCommand: public ICommand<Args...> {
public:
    virtual ~MctCommand() = default;

    bool execute(Args...args) override;

    bool operator()(Args...args) override;

    static std::unique_ptr<ICommand<Args...>>> create();
};

}

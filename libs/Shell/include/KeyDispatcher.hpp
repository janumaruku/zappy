/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** KeyDispatcher
*/

#ifndef SHELL_KEY_DISPATCHER_HPP
#define SHELL_KEY_DISPATCHER_HPP

#include <functional>
#include <string>
#include <unordered_map>

#include "LineBuffer.hpp"

namespace shell {

class KeyDispatcher {
public:
    using Action = std::function<void(LineBuffer &)>;

    KeyDispatcher();

    void bind(std::string sequence, Action action);
    bool dispatch(const std::string &sequence, LineBuffer &buf) const;

private:
    void registerDefaults();

    std::unordered_map<std::string, Action> _bindings;
};

} // namespace shell

#endif // SHELL_KEY_DISPATCHER_HPP

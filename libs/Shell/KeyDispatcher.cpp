/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** KeyDispatcher
*/

#include "KeyDispatcher.hpp"

namespace shell {

KeyDispatcher::KeyDispatcher()
{
    registerDefaults();
}

void KeyDispatcher::registerDefaults()
{
    _bindings["\x7f"]     = [](LineBuffer &b) { b.eraseBefore(); }; // ⌫
    _bindings["\x08"]     = [](LineBuffer &b) { b.eraseBefore(); }; // Ctrl+H
    _bindings["\x1b[C"]   = [](LineBuffer &b) { b.moveRight(); };   // →
    _bindings["\x1b[D"]   = [](LineBuffer &b) { b.moveLeft(); };    // ←
    _bindings["\x1b[A"]   = [](LineBuffer &) {};                     // ↑ (history placeholder)
    _bindings["\x1b[B"]   = [](LineBuffer &) {};                     // ↓ (history placeholder)
    _bindings["\x1b[H"]   = [](LineBuffer &b) { b.moveHome(); };    // Home
    _bindings["\x1b[F"]   = [](LineBuffer &b) { b.moveEnd(); };     // End
}

void KeyDispatcher::bind(std::string sequence, Action action)
{
    _bindings[std::move(sequence)] = std::move(action);
}

bool KeyDispatcher::dispatch(const std::string &sequence, LineBuffer &buf) const
{
    const auto it = _bindings.find(sequence);
    if (it == _bindings.end())
        return false;
    it->second(buf);
    return true;
}

} // namespace shell
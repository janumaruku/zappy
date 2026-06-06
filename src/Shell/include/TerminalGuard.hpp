/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** TerminalGuard
*/

#pragma once

#include <termios.h>

namespace shell {

class TerminalGuard {
public:
    TerminalGuard();

    ~TerminalGuard();

    TerminalGuard(const TerminalGuard &) = delete;

    TerminalGuard &operator=(const TerminalGuard &) = delete;

    TerminalGuard(TerminalGuard &&) = delete;

    TerminalGuard &operator=(TerminalGuard &&) = delete;

    void disable() noexcept;

private:
    termios _saved;
    bool _active;
};

} // namespace shell

/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** TerminalGuard
*/

#ifndef SHELL_TERMINAL_GUARD_HPP
#define SHELL_TERMINAL_GUARD_HPP

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

#endif // SHELL_TERMINAL_GUARD_HPP

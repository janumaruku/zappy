/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** TerminalGuard
*/

#include "TerminalGuard.hpp"

#include <unistd.h>

namespace shell {

TerminalGuard::TerminalGuard() : _active{false}
{
    tcgetattr(STDIN_FILENO, &_saved);

    struct termios raw = _saved;
    raw.c_lflag &= ~static_cast<tcflag_t>(ECHO | ICANON);
    raw.c_cc[VMIN]  = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    _active = true;
}

TerminalGuard::~TerminalGuard()
{
    disable();
}

void TerminalGuard::disable() noexcept
{
    if (!_active)
        return;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &_saved);
    _active = false;
}

} // namespace shell
/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** LineBuffer
*/

#ifndef SHELL_LINE_BUFFER_HPP
#define SHELL_LINE_BUFFER_HPP

#include <cstddef>
#include <string>

namespace shell {

class LineBuffer {
public:
    void insert(char c);

    void eraseBefore();

    void eraseAt();

    void moveLeft();

    void moveRight();

    void moveHome();

    void moveEnd();

    void clear();

    [[nodiscard]] const std::string &text() const noexcept;

    [[nodiscard]] std::size_t cursor() const noexcept;

    [[nodiscard]] bool atStart() const noexcept;

    [[nodiscard]] bool atEnd() const noexcept;

private:
    std::string _text;
    std::size_t _cursor = 0;
};

} // namespace shell

#endif // SHELL_LINE_BUFFER_HPP

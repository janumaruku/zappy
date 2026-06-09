/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** LineBuffer
*/

#include "LineBuffer.hpp"

namespace shell {

void LineBuffer::insert(char c)
{
    _text.insert(_cursor, 1, c);
    ++_cursor;
}

void LineBuffer::eraseBefore()
{
    if (_cursor == 0)
        return;
    _text.erase(_cursor - 1, 1);
    --_cursor;
}

void LineBuffer::eraseAt()
{
    if (_cursor == _text.size())
        return;
    _text.erase(_cursor, 1);
}

void LineBuffer::moveLeft()
{
    if (_cursor > 0)
        --_cursor;
}

void LineBuffer::moveRight()
{
    if (_cursor < _text.size())
        ++_cursor;
}

void LineBuffer::moveHome()
{
    _cursor = 0;
}

void LineBuffer::moveEnd()
{
    _cursor = _text.size();
}

void LineBuffer::clear()
{
    _text.clear();
    _cursor = 0;
}

const std::string &LineBuffer::text() const noexcept
{
    return _text;
}

std::size_t LineBuffer::cursor() const noexcept
{
    return _cursor;
}

bool LineBuffer::atStart() const noexcept
{
    return _cursor == 0;
}

bool LineBuffer::atEnd() const noexcept
{
    return _cursor == _text.size();
}

} // namespace shell
/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Buffer
*/

#include "Buffer.hpp"

namespace network {
ConstBuffer buffer(const std::string &str) noexcept
{
    return ConstBuffer {
        .data = str.data(),
        .size = str.size()
    };
}

MutableBuffer buffer(std::string &str, const std::size_t &size)
{
    return MutableBuffer {
        .data = str.data(),
        .size = size
    };
}
} // ftp

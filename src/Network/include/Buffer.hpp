/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Buffer
*/

#ifndef MYFTP_BUFFER_HPP
#define MYFTP_BUFFER_HPP

#include <cstring>
#include <string>
#include <vector>

namespace network {
struct ConstBuffer {
    const void *data;
    std::size_t size;
};

struct MutableBuffer {
    void *data;
    std::size_t size;

    operator ConstBuffer() const;
};

ConstBuffer buffer(const std::string &str) noexcept;

MutableBuffer buffer(std::string &str, const std::size_t &size);

template <typename PodType>
ConstBuffer buffer(const PodType *buff)
{
    return ConstBuffer {
        .data = buff,
        .size = strlen(buff)
    };
}

template <typename PodType>
MutableBuffer buffer(std::vector<PodType> &vec)
{
    return MutableBuffer {
        .data = vec.data(),
        .size = vec.size()
    };
}

template <typename PodType>
ConstBuffer buffer(const std::vector<PodType> &vec)
{
    return ConstBuffer {
        .data = vec.data(),
        .size = vec.size()
    };
}
} // ftp

#endif //MYFTP_BUFFER_HPP

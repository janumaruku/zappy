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
/**
 * @struct ConstBuffer
 * @brief A read-only view over a contiguous block of bytes.
 *
 * `ConstBuffer` does not own the memory it points to. It is just a raw pointer
 * and a size, used to pass data to write operations like @ref ConnectedSocket::asyncWrite.
 * Make sure the underlying data stays alive for the duration of the async operation.
 * See the buffer lifetime warning in the @ref async_model page.
 *
 * Use the @ref network::buffer factory functions to create a @ref ConstBuffer from a string or vector.
 */
struct ConstBuffer {
    const void *data; ///< Pointer to the beginning of the data.
    std::size_t size; ///< Number of bytes.
};

/**
 * @struct MutableBuffer
 * @brief A writable view over a contiguous block of bytes.
 *
 * @ref MutableBuffer does not own the memory it points to. It is used to pass a
 * destination buffer to read operations like @ref ConnectedSocket::asyncReadSome.
 * The same lifetime rules apply as for @ref ConstBuffer.
 *
 * It can be implicitly converted to a @ref ConstBuffer when a read-only view is needed.
 *
 * Use the @ref network::buffer factory functions to create a @ref MutableBuffer from a string or vector.
 */
struct MutableBuffer {
    void *data;       ///< Pointer to the beginning of the writable memory.
    std::size_t size; ///< Number of bytes available.

    /// @brief Converts this buffer to a read-only @ref ConstBuffer.
    operator ConstBuffer() const;
};

/**
 * @brief Creates a @ref ConstBuffer from a string. The string must outlive the buffer.
 * @param str The source string.
 */
ConstBuffer buffer(const std::string &str) noexcept;

/**
 * @brief Creates a @ref MutableBuffer from a string, limited to @p size bytes.
 * @param str  The destination string.
 * @param size Maximum number of bytes that can be read.
 */
MutableBuffer buffer(std::string &str, const std::size_t &size);

/**
 * @brief Creates a @ref ConstBuffer from a null-terminated POD pointer.
 * @param buff Pointer to the data. Size is determined with `strlen`.
 */
template <typename PodType>
ConstBuffer buffer(const PodType *buff)
{
    return ConstBuffer {
        .data = buff,
        .size = strlen(buff)
    };
}

/**
 * @brief Creates a @ref MutableBuffer from a vector. The vector must outlive the buffer.
 * @param vec The destination vector.
 */
template <typename PodType>
MutableBuffer buffer(std::vector<PodType> &vec)
{
    return MutableBuffer {
        .data = vec.data(),
        .size = vec.size()
    };
}

/**
 * @brief Creates a @ref ConstBuffer from a const vector. The vector must outlive the buffer.
 * @param vec The source vector.
 */
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

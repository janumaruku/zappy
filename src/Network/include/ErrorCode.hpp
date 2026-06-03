/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ErrorCode
*/

#ifndef MYFTP_ERRORCODE_HPP
#define MYFTP_ERRORCODE_HPP

#include <cstdint>
#include <system_error>
#include <type_traits>

enum class FtpErrorCode : uint8_t {
    CONNECTION_LIMIT_REACHED = 1,

    CS_WRITE_ERROR,
    CS_READ_ERROR,

    RETRY_ACCEPT,
    ACCEPT_BAD_FILE_DESCRIPTOR,
    ACCEPT_BAD_ADDRESS,
    ACCEPT_INVALID_STATE,
    ACCEPT_OPERATION_NOT_SUPPORTED,
    ACCEPT_RESOURCE_EXHAUSTED,
    ACCEPT_PERMISSION_DENIED,
    ACCEPT_PROTOCOL_ERROR,
    ACCEPT_UNKNOWN_ERROR,
};

template <> struct std::is_error_code_enum<FtpErrorCode>: true_type {};

struct FtpErrorCodeCategory: std::error_category {
    [[nodiscard]] const char *name() const noexcept override;

    [[nodiscard]] std::string message(int errorValue) const override;

    std::error_condition
        default_error_condition(int errorValue) const noexcept override;
};

inline const FtpErrorCodeCategory &ftpCategory() noexcept
{
    static const FtpErrorCodeCategory category{};

    return category;
}

std::error_code make_error_code(FtpErrorCode errCode) noexcept; // NOLINT

#endif //MYFTP_ERRORCODE_HPP

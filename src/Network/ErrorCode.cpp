/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** ErrorCode
*/

#include "ErrorCode.hpp"

#include <cstring>

const char *FtpErrorCodeCategory::name() const noexcept
{
    return "AcceptorError";
}

std::string FtpErrorCodeCategory::message(int errorValue) const
{
    switch (static_cast<FtpErrorCode>(errorValue)) {
    case FtpErrorCode::CONNECTION_LIMIT_REACHED:
        return "Connection limit reached";
    case FtpErrorCode::CS_WRITE_ERROR:
        return "Failed to write to client socket";
    case FtpErrorCode::CS_READ_ERROR:
        return std::string{"Failed to read from client socket, "} + strerror(
            errno);
    case FtpErrorCode::RETRY_ACCEPT:
        return "Retry to accept incoming client";
    case FtpErrorCode::ACCEPT_BAD_FILE_DESCRIPTOR:
        return "Listening socket file descriptor is invalid";
    case FtpErrorCode::ACCEPT_BAD_ADDRESS:
        return "accept() received an invalid address buffer";
    case FtpErrorCode::ACCEPT_INVALID_STATE:
        return "Listening socket is not in a valid state for accept()";
    case FtpErrorCode::ACCEPT_OPERATION_NOT_SUPPORTED:
        return "accept() is not supported for this socket type";
    case FtpErrorCode::ACCEPT_RESOURCE_EXHAUSTED:
        return "Server resource exhausted";
    case FtpErrorCode::ACCEPT_PERMISSION_DENIED:
        return "Permission denied while accepting a new client";
    case FtpErrorCode::ACCEPT_PROTOCOL_ERROR:
        return "Protocol error occurred while accepting a new client";
    default:
        return "Unknown error";
    }
}

std::error_condition FtpErrorCodeCategory::default_error_condition(
    const int errorValue) const noexcept
{
    return {errorValue, *this};
}

std::error_code make_error_code(FtpErrorCode errCode) noexcept
{
    return {static_cast<int>(errCode), ftpCategory()};
}

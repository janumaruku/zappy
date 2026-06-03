/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Endpoint
*/

#include "Endpoint.hpp"

#include <array>
#include <iostream>
#include <stdexcept>
#include <arpa/inet.h>

#include "constants.hpp"

namespace network {
Endpoint::Endpoint(const int &port, const std::string &hostName): _port{port},
    _hostName{hostName}
{
    _address.sin_family = AF_INET;
    _address.sin_port   = htons(_port);
    if (hostName.empty())
        _address.sin_addr.s_addr = INADDR_ANY;
    else {
        const int inetResult = inet_pton(AF_INET, hostName.c_str(),
            &_address.sin_addr);

        if (inetResult == 0)
            throw std::runtime_error("Invalid network address");
        if (inetResult == -1)
            throw std::runtime_error("Invalid network address family");
    }
}

Endpoint::Endpoint(const sockaddr_in &address): _address{address}
{}

int Endpoint::getPort() const noexcept
{
    return ntohs(_address.sin_port);
}

std::string Endpoint::getHostname() const noexcept
{
    std::array<char, INET_ADDRSTRLEN> buf{};
    const char *res = inet_ntop(
        AF_INET,
        &_address.sin_addr,
        buf.data(),
        buf.size()
        );
    if (!res) {
        return {};
    }
    return std::string{buf.data()};
}

sockaddr_in &Endpoint::getAddress() noexcept
{
    return _address;
}
} // ftp

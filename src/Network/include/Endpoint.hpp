/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Endpoint
*/

#ifndef MYFTP_ENDPOINT_HPP
#define MYFTP_ENDPOINT_HPP

#include <string>
#include <netinet/in.h>

namespace network {
class Endpoint {
public:
    Endpoint() = default;

    explicit Endpoint(const int &port, const std::string &hostName = "");

    explicit Endpoint(const sockaddr_in &address);

    [[nodiscard]] int getPort() const noexcept;

    [[nodiscard]] std::string getHostname() const noexcept;

    sockaddr_in &getAddress() noexcept;

private:
    int _port = 0;
    std::string _hostName;
    sockaddr_in _address{};
};
} // ftp

#endif //MYFTP_ENDPOINT_HPP

/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Endpoint
*/

#ifndef ZAPPY_ENDPOINT_HPP
#define ZAPPY_ENDPOINT_HPP

#include <string>
#include <netinet/in.h>

namespace network {
/**
 * @class Endpoint
 * @brief Holds the IP address and port that identify one side of a TCP connection.
 *
 * It wraps a @c sockaddr_in and is used throughout the library wherever an address
 * is needed, for example when constructing an @ref Acceptor or a @ref ConnectedSocket.
 */
class Endpoint {
public:
    Endpoint() = default;

    /**
     * @brief Constructs an endpoint from a port number and an optional hostname.
     * @param port     The port number.
     * @param hostName IPv4 address as a string. Defaults to @c INADDR_ANY when empty.
     */
    explicit Endpoint(const int &port, const std::string &hostName = "");

    /**
     * @brief Constructs an endpoint from an existing @c sockaddr_in structure.
     * @param address The address structure, typically received from @c accept().
     */
    explicit Endpoint(const sockaddr_in &address);

    /// @brief Returns the port number.
    [[nodiscard]] int getPort() const noexcept;

    /// @brief Returns the hostname or IP address as a string.
    [[nodiscard]] std::string getHostname() const noexcept;

    /// @brief Returns a reference to the underlying @c sockaddr_in structure.
    [[nodiscard]] const sockaddr_in &getAddress() const noexcept;

private:
    int _port = 0;           ///< Port number.
    std::string _hostName;   ///< Hostname or IP address.
    sockaddr_in _address{};  ///< Underlying socket address structure.
};
} // ftp

#endif //ZAPPY_ENDPOINT_HPP

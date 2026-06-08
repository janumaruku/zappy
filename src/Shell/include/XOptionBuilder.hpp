/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** XOptionBuilder
*/

#ifndef ZAPPY_XOPTION_HPP
#define ZAPPY_XOPTION_HPP
#include <string>

#include "CommandDefinition.hpp"


namespace shell::command {
class XOptionBuilder {
public:
    XOptionBuilder &name(const std::string &name) noexcept;

    XOptionBuilder &description(const std::string &description) noexcept;

    XOptionBuilder &alias(const std::string &alias) noexcept;

    XOptionBuilder &min(const std::size_t &min) noexcept;

    XOptionBuilder &required() noexcept;

    [[nodiscard]] XOption build() const noexcept;

private:
    XOption _option;
};
} // command
// shell

#endif //ZAPPY_XOPTION_HPP

/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** constants
*/

#ifndef MYTEAMS_CONSTANTS_HPP
#define MYTEAMS_CONSTANTS_HPP

#include <random>
#include <string>

namespace utils {
constexpr std::string RESET   = "\033[0m";
constexpr std::string RED     = "\033[31m";
constexpr std::string GREEN   = "\033[32m";
constexpr std::string YELLOW  = "\033[33m";
constexpr std::string BLUE    = "\033[34m";
constexpr std::string MAGENTA = "\033[35m";
constexpr std::string CYAN    = "\033[96m";

template <typename T>
T randomNumber(const T &low, const T &high)
{
    static std::mt19937 generator(std::random_device{}());

    if constexpr (std::is_integral_v<T>) {
        std::uniform_int_distribution<T> distribution(low, high);
        return distribution(generator);
    } else {
        std::uniform_real_distribution<T> distribution(low, high);
        return distribution(generator);
    }
}
}

#endif //MYTEAMS_CONSTANTS_HPP

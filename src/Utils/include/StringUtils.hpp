/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** StringUtils
*/

#ifndef MYTEAMS_STRINGUTILS_HPP
#define MYTEAMS_STRINGUTILS_HPP

#include <string>
#include <vector>

namespace utils {
class StringUtils {
public:
    static std::string cleanString(const std::string &str) noexcept;

    static std::vector<std::string> split(const std::string &str) noexcept;

    static std::vector<std::string> splitQuoted(const std::string &str);

    static std::vector<std::string> split(const std::string &str,
        const char &delim);

    static std::string spaces(std::size_t size) noexcept;

    static std::string fillChars(std::size_t size, char character) noexcept;

    static std::size_t beginSpacesCount(const std::string &str);

    static short stos(const std::string &str);

    static std::string toLower(const std::string &value);

    static std::string toString(const std::vector<std::string> &words,
        const char &join);

    static bool contains(const std::string & str, const char &chr);
};
} // utils

#endif //MYTEAMS_STRINGUTILS_HPP

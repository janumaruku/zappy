/*
** EPITECH PROJECT, 2026
** NanoTekSpice
** File description:
** StringUtils
*/

#include <algorithm>
#include <regex>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <exception>
#include "StringUtils.hpp"

namespace utils {
std::string StringUtils::cleanString(const std::string &str) noexcept
{
    std::stringstream stream{str};
    std::string word;
    std::string remaining;

    stream >> word;

    std::getline(stream, remaining);

    if (remaining.back() == '\r')
        remaining.pop_back();

    return word + remaining;
}

std::vector<std::string> StringUtils::splitQuoted(const std::string &str)
{
    bool inQuotes = false;
    std::string tmp;
    std::vector<std::string> result;

    for (auto current : str) {
        if (current == '"') {
            if (inQuotes)
                result.push_back(tmp);
            tmp.clear();
            inQuotes = !inQuotes;
           continue;
        }
        if (!inQuotes && current == ' ') {
            if (!tmp.empty()) {
                result.push_back(tmp);
                tmp.clear();
            }
            continue;
        }
        tmp.push_back(current);
    }

    if (!tmp.empty())
        result.push_back(tmp);
    return result;
}


std::vector<std::string> StringUtils::split(const std::string &str) noexcept
{
    std::vector<std::string> result;
    std::stringstream stream{str};
    std::string word;

    while (stream >> word)
        result.push_back(word);

    return result;
}

std::vector<std::string> StringUtils::split(const std::string &str,
    const char &delim)
{
    std::vector<std::string> result;
    std::string word;

    std::string temStr = str;
    while (temStr.front() == delim)
        temStr.erase(0, 1);
    std::stringstream stream{temStr};

    while (std::getline(stream, word, delim)) {
        result.push_back(word);
    }
    return result;
}

std::string StringUtils::spaces(const std::size_t size) noexcept
{
    std::string result;

    for (std::size_t i = 0; i < size; ++i)
        result += " ";

    return result;
}

std::string StringUtils::fillChars(const std::size_t size,
    const char character) noexcept
{
    std::string result;

    for (std::size_t i = 0; i < size; ++i)
        result += character;

    return result;
}

std::size_t StringUtils::beginSpacesCount(const std::string &str)
{
    std::size_t count = 0;

    while (str[count] == ' ' && count < str.size() - 1)
        ++count;

    return count;
}

short StringUtils::stos(const std::string &str)
{
    const int num = std::stoi(str);

    if (num > std::numeric_limits<short>::max() || num < std::numeric_limits<
        short>::min())
        throw std::out_of_range(str + " is out of range of short");

    return static_cast<short>(num);
}

std::string StringUtils::toLower(const std::string &value)
{
    std::string result;

    for (const char &character : value)
        result += std::tolower(character);

    return result;
}

std::string StringUtils::toString(const std::vector<std::string> &words,
    const char &join)
{
    std::string res;

    for (const auto &word: words)
        res += word + join;

    res.pop_back();

    return res;
}

bool StringUtils::contains(const std::string &str, const char &chr)
{
    for (const auto &elem: str) {
        if (elem == chr)
            return true;
    }

    return  false;
}
} // utils

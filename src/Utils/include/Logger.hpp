/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Logger
*/

#ifndef MYFTP_LOGGER_HPP
#define MYFTP_LOGGER_HPP

#include <cstdint>
#include <iostream>
#include <string>

namespace utils {
class Logger {
public:
    enum class Level: std::uint8_t {
        ERROR,
        WARNING,
        DEBUG_LEVEL,
        INFO,
    };

    struct EndLogger {};

    inline static const EndLogger END;

    explicit Logger(std::string context, const Level &level,
        const bool &isEnabled);

    template <typename T>
    Logger &operator<<(const T &value)
    {
        if (!_isEnabled || !_shouldPrint)
            return *this;

        *_stream << value;

        return *this;
    }

    Logger &operator<<(const EndLogger &);

    Logger &start(const Level &level, const std::string &context = "");

private:
    bool _isEnabled   = true;
    bool _shouldPrint = true;
    std::string _context;
    Level _level          = Level::INFO;
    std::ostream *_stream = &std::cout;

    void setLevelColor(const Level &level) const;

    void chooseOutputStream(const Level &);
};
constexpr Logger::EndLogger END = Logger::END;
} // utils
using ULogLevel = utils::Logger::Level;

#endif //MYFTP_LOGGER_HPP

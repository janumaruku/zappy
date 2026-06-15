/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Logger
*/

#ifndef ZAPPY_LOGGER_HPP
#define ZAPPY_LOGGER_HPP

#include <cstdint>
#include <iostream>
#include <string>

namespace utils {
struct LoggerConfig;

class Logger {
public:
    enum class Level: std::uint8_t {
        INFO = 0,
        DEBUG_LEVEL,
        WARNING,
        ERROR,
    };

    struct EndLogger {
    };

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

    void config(const LoggerConfig &config);

private:
    bool _isEnabled = true;
    bool _shouldPrint = true;
    std::string _context;
    Level _level = Level::INFO;
    std::ostream *_stream = &std::cout;

    void setLevelColor(const Level &level) const;

    void chooseOutputStream(const Level &);
};

struct LoggerConfig {
    std::string context;
    Logger::Level level;
    bool enabled;
};

constexpr Logger::EndLogger END = Logger::END;
} // utils
using LogLevel = utils::Logger::Level;

bool operator<(const LogLevel &lhs, const LogLevel &rhs);

bool operator==(const LogLevel &lhs, const LogLevel &rhs);

#endif //ZAPPY_LOGGER_HPP

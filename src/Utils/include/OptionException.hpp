/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** OptionException
*/

#ifndef MYFTP_OPTIONEXCEPTION_HPP
#define MYFTP_OPTIONEXCEPTION_HPP

#include <exception>
#include <string>

namespace utils {
class OptionException: public std::exception {
public:
    explicit OptionException(const std::string &option,
        const std::string &message);

    [[nodiscard]] const char *what() const noexcept override;

protected:
    std::string _message;
};
} // namespace utils

#endif // MYFTP_OPTIONEXCEPTION_HPP

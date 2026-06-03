/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** IOptionHandler
*/

#ifndef MYFTP_IOPTIONHANDLER_HPP
#define MYFTP_IOPTIONHANDLER_HPP

#include <string>
#include <vector>

namespace utils {
class IOptionHandler {
public:
    IOptionHandler() = default;

    virtual ~IOptionHandler() = default;

    virtual bool operator()(const std::vector<std::string> &args,
        std::vector<std::string> &tempArgs) = 0;

    virtual std::string getOption() const noexcept = 0;

    [[nodiscard]] virtual bool hasOption() const noexcept = 0;
};
} // utils

#endif //MYFTP_IOPTIONHANDLER_HPP

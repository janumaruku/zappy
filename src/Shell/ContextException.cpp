/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** ContextException
*/

#include "ContextException.hpp"

#include "constants.hpp"

namespace shell::command {
const char *ContextException::what() const noexcept
{
    return _message.c_str();
}

MissingArgumentException::MissingArgumentException(const std::string &name)
{
    _message = utils::RED + "Error: " + utils::RESET +
        "Missing required argument " + utils::RED + name + utils::RESET;
}

MissingOptionException::MissingOptionException(const std::string &name)
{
    _message = utils::RED + "Error: " + utils::RESET +
        "Missing required option " + utils::RED + name + utils::RESET;
}

MissingFlagException::MissingFlagException(const std::string &name)
{
    _message = utils::RED + "Error: " + utils::RESET +
        "Missing required flag " + utils::RED + name + utils::RESET;
}

MissingOptionValueException::MissingOptionValueException(
    const std::string &name)
{
    _message = utils::RED + "Error: " + utils::RESET +
        "Missing argument for option " + utils::RED + name + utils::RESET;
}

UnknownTokenException::UnknownTokenException(const std::string &token)
{
    _message = utils::RED + "Error: " + utils::RESET +
        "Unknown option or flag " + utils::RED + token + utils::RESET;
}

UnexpectedArgumentException::UnexpectedArgumentException(
    const std::string &token)
{
    _message = utils::RED + "Error: " + utils::RESET +
        "Unexpected argument " + utils::RED + token + utils::RESET;
}
} // namespace shell::command

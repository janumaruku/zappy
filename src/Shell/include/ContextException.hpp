/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** ContextException
*/

#pragma once

#include <exception>
#include <string>

namespace shell::command {
class ContextException : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override;

protected:
    std::string _message;
};

class MissingArgumentException : public ContextException {
public:
    explicit MissingArgumentException(const std::string &name);
};

class MissingOptionException : public ContextException {
public:
    explicit MissingOptionException(const std::string &name);
};

class MissingFlagException : public ContextException {
public:
    explicit MissingFlagException(const std::string &name);
};

class MissingOptionValueException : public ContextException {
public:
    explicit MissingOptionValueException(const std::string &name);
};

class UnknownTokenException : public ContextException {
public:
    explicit UnknownTokenException(const std::string &token);
};

class UnexpectedArgumentException : public ContextException {
public:
    explicit UnexpectedArgumentException(const std::string &token);
};
} // namespace shell::command

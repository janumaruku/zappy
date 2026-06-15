/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Options
*/

#include "Options.hpp"

#include <iostream>
#include <ranges>

#include "OptionException.hpp"

namespace utils {
Options::Options(char *argv[])
{
    for (std::size_t i = 0; argv[i] != nullptr; ++i)
        _args.emplace_back(argv[i]);
    _tempArgs = _args;
}

std::vector<std::string> Options::processArgs()
{
    auto hasOption = false;
    for (const auto &arg: _args)
        if (arg[0] == '-') {
            hasOption = true;
            break;
        }
    if (!hasOption)
        return _tempArgs;

    std::size_t itt = 0;
    while (itt < _tempArgs.size()) {
        if (_tempArgs[itt][0] != '-') {
            ++itt;
            continue;
        }

        if (!_optionHandlerMap.contains(_tempArgs[itt]))
            throw OptionException{_tempArgs[itt], "Unknown option"};
        (*_optionHandlerMap[_tempArgs[itt]])(_args, _tempArgs);
    }

    return _tempArgs;
}

std::string Options::getOption(const std::string &option)
{
    const auto itt = _optionHandlerMap.find(option);

    if (itt == _optionHandlerMap.end())
        throw std::logic_error("Unknown option \"" + option + "\"");

    return itt->second->getOption();
}

bool Options::hasOption(const std::string &option)
{
    const auto itt = _optionHandlerMap.find(option);

    if (itt == _optionHandlerMap.end())
        throw std::logic_error("Unknown option \"" + option + "\"");

    return itt->second->hasOption();
}
} // namespace utils

/*
** EPITECH PROJECT, 2026
** myftp
** File description:
** Options
*/

#ifndef MYFTP_OPTIONS_HPP
#define MYFTP_OPTIONS_HPP

#include <string>
#include <vector>

#include "FactoryTemplate.hpp"
#include "IOptionHandler.hpp"

namespace utils {

class Options {
public:
    using OptionHandlerFactory =
    designPattern::FactoryTemplate<IOptionHandler, std::string>;
    using OptionHandlerMap =
    std::unordered_map<std::string, std::unique_ptr<IOptionHandler>>;

    explicit Options(char *argv[]);

    template <typename ConcreteClass>
        requires designPattern::HasCreateMethod<IOptionHandler, ConcreteClass>
    void registerOptionHandler(const std::string &option)
    {
        _optionHandlerFactory.registerCreator<ConcreteClass>(option);
        _optionHandlerMap[option] = _optionHandlerFactory.create(option);
    }

    std::vector<std::string> processArgs();

    std::string getOption(const std::string &option);

    bool hasOption(const std::string &option);

private:
    std::vector<std::string> _args;
    std::vector<std::string> _tempArgs;
    OptionHandlerFactory _optionHandlerFactory;
    OptionHandlerMap _optionHandlerMap;
};

} // namespace utils

#endif // MYFTP_OPTIONS_HPP

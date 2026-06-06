/*
** EPITECH PROJECT, 2026
** Shell
** File description:
** Prompt
*/

#pragma once

#include <functional>
#include <optional>
#include <string>

#include "KeyDispatcher.hpp"
#include "LineBuffer.hpp"

namespace shell {

class Prompt {
public:
    explicit Prompt(std::string promptStr, std::function<void()> onIdle = {});

    std::optional<std::string> getline();

    void setPrompt(std::string promptStr) noexcept;

    const std::string &getPrompt() const noexcept;

private:
    std::string _prompt_str;
    std::function<void()> _on_idle;
    LineBuffer _buffer;
    KeyDispatcher _dispatcher;

    static std::string readSequence();

    void redraw() const;

    static void eraseLine() ;
};

} // namespace shell

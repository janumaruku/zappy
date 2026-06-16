/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** AObserver
*/

#include "AObserver.hpp"

namespace designPattern
{
AObserver::AObserver(
    const std::initializer_list<std::pair<int, ISubject &>> &subjects)
{
    for (const auto &[key, subject] : subjects) {
        subject.addObserver(key, this);
        _subjects.emplace_back(key, subject);
    }
}

AObserver::~AObserver()
{
    for (const auto &[key, subject] : _subjects)
        subject.removeObserver(key, this);
}
} // designPattern
/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ASubject
*/

#include "ASubject.hpp"

#include <ranges>
#include <stdexcept>

#include "IObserver.hpp"

namespace designPattern {
void ASubject::addObserver(int observerType, IObserver *observer)
{
    if (!_observers.contains(observerType))
        _observers.emplace(observerType, ObserverList{});

    _observers[observerType].push_front(observer);
}

void ASubject::removeObserver(int observerType, IObserver *observer)
{
    auto it = _observers.find(observerType);

    if (it != _observers.end())
        it->second.remove(observer);
    else
        throw std::out_of_range("Unknown observer type");
}

void ASubject::notifyAll()
{
    for (auto &observerList: _observers | std::ranges::views::values) {
        for (const auto &observer: observerList) {
            observer->onNotify();
        }
    }
}
} // designPattern

/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ASubject.tpp
*/

#pragma once

#include <exception>
#include <ranges>
#include <stdexcept>
#include "ASubject.hpp"

namespace designPattern {

template <typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::addObserver(KeyType observerType,
    IObserver<EventType> *observer)
{
    _observers[observerType].emplace_front(observer);
}

template <typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::removeObserver(KeyType observerType,
    IObserver<EventType> *observer)
{
    auto &list = _observers[observerType];
    if (std::ranges::find(list, observer) == list.end())
        throw std::out_of_range("Observer type not found");
    list.remove(observer);
}

template <typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::notify(KeyType observerType,
    const EventType &event)
{
    if (!_observers.contains(observerType))
        return;
    for (const auto &observer: _observers[observerType])
        observer->onNotify(event);
}

template <typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::notifyAll(const EventType &event)
{
    for (const auto keyType: _observers | std::ranges::views::keys)
        notify(keyType, event);
}

}

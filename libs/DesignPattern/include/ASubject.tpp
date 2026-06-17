/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ASubject.tpp
*/

#pragma once

#include <exception>
#include <stdexcept>
#include "ASubject.hpp"

namespace designPattern {

template<typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::addObserver(KeyType observerType, IObserver<EventType>* observer)
{
    _observers[observerType].emplace_front(observer);
}

template<typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::removeObserver(KeyType observerType, IObserver<EventType>* observer)
{
    if (!_observers[observerType].contains(observer))
        throw std::out_of_range("Observer type not found");
    _observers[observerType].remove(observer);
}

template<typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::notify(KeyType observerType, const EventType &event)
{
    try {
        _observers[observerType];
    } catch (const std::exception &) {
        return;
    }
    for (const auto &observer : _observers[observerType])
        observer.onNotify(event);
}

template<typename EventType, typename KeyType>
void ASubject<EventType, KeyType>::notifyAll(const EventType &event)
{
    for (const auto &[keyType, list] : _observers)
        notify(keyType, event);
}

}
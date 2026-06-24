/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ISubject.hpp
*/

#pragma once

#include "IObserver.hpp"

namespace designPattern {

template<typename EventType, typename KeyType>
class ISubject {
public:
    virtual ~ISubject() = default;

    virtual void addObserver(KeyType observerType, IObserver<EventType>* observer) = 0;

    virtual void removeObserver(KeyType observerType, IObserver<EventType>* observer) = 0;

    virtual void notify(KeyType observerType, const EventType& event) = 0;

    virtual void notifyAll(const EventType& event) = 0;
};
}
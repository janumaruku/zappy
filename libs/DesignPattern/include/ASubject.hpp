/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** ASubject.hpp
*/


#pragma once

#include <forward_list>
#include <unordered_map>
#include "ISubject.hpp"

namespace designPattern {

template<typename EventType, typename KeyType>
class ASubject : public ISubject<EventType, KeyType> {
public:
    ~ASubject() override = default;

    void addObserver(KeyType observerType, IObserver<EventType>* observer) override;

    void removeObserver(KeyType observerType, IObserver<EventType>* observer) override;

    void notify(KeyType observerType, const EventType &event) override;

    void notifyAll(const EventType& event) override;

protected:
    std::unordered_map<KeyType, std::forward_list<IObserver<EventType>*>> _observers;
};

}

#include "ASubject.tpp"

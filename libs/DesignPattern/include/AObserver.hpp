/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AObserver.hpp
*/

#pragma once

#include <initializer_list>
#include <utility>
#include <vector>
#include "IObserver.hpp"
#include "ISubject.hpp"

namespace designPattern {

template<typename EventType, typename KeyType>
class AObserver : IObserver<EventType>{
public:
    ~AObserver() override;

    AObserver(const AObserver &) = delete;
    AObserver(AObserver &&) = delete;


    AObserver(const std::initializer_list<std::pair<KeyType, ISubject<EventType, KeyType>&>>&);

    void onNotify(const EventType &event) override;

protected:
    std::vector<std::pair<KeyType, ISubject<EventType, KeyType>&>> _subjects;
};

}

#include "AObserver.tpp"
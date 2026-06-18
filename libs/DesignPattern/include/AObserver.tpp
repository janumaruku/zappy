/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** AObserver.cpp
*/

#pragma once

#include "AObserver.hpp"

namespace designPattern {

template<typename EventType, typename KeyType>
AObserver<EventType, KeyType>::AObserver(const std::initializer_list<std::pair<KeyType, ISubject<EventType, KeyType>&>>& pairs)
{
    for (const auto &[key, subject] : pairs) {
        subject.addObserver(key, this);
        _subjects.emplace_back(key, subject);
    }
}

template<typename EventType, typename KeyType>
AObserver<EventType, KeyType>::~AObserver()
{
    for (const auto &[key, subject] : _subjects)
        subject.removeObserver(key, this);
}

}
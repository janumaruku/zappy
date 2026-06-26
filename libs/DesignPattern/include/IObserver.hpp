/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** IObserver.hpp
*/

#pragma once

namespace designPattern {

template<typename EventType>
class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void onNotify(const EventType &event) = 0;
};

}
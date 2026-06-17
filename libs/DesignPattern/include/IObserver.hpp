/*
** EPITECH PROJECT, 2025
** ZPY
** File description:
** IObserver.hpp
*/

#pragma once

namespace designPattern {

template<typename EventType>
class IObserver {
public:
    virtual ~IObserver() = 0;

    virtual void onNotify(const EventType &event) = 0;
};

}
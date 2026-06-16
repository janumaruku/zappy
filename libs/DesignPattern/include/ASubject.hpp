/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ASubject
*/

#ifndef ZAPPY_ASUBJECT_HPP
#define ZAPPY_ASUBJECT_HPP

#include <forward_list>
#include <unordered_map>

#include "ISubject.hpp"

namespace designPattern {
class ASubject: public ISubject {
public:
    void addObserver(int observerType, IObserver *observer) override;

    void removeObserver(int observerType, IObserver *observer) override;

    void notifyAll() override;

protected:
    using ObserverList = std::forward_list<IObserver *>;
    using ObserverMap = std::unordered_map<int, ObserverList>;

    ObserverMap _observers;
};
} // designPattern

#endif //ZAPPY_ASUBJECT_HPP

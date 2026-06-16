/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** ISubject
*/

#ifndef ZAPPY_ISUBJECT_HPP
#define ZAPPY_ISUBJECT_HPP

namespace designPattern {
class IObserver;

class ISubject {
public:
    virtual ~ISubject() = default;

    virtual void addObserver(int observerType, IObserver *observer) = 0;

    virtual void removeObserver(int observerType, IObserver *observer) = 0;

    virtual void notifyAll() = 0;
};
} // designPattern

#endif //ZAPPY_ISUBJECT_HPP

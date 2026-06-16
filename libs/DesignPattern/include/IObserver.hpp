/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** IObserver
*/

#ifndef ZAPPY_IOBSERVER_HPP
#define ZAPPY_IOBSERVER_HPP

namespace designPattern {
class ISubject;

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void onNotify() = 0;
};
} // design_pattern

#endif //ZAPPY_IOBSERVER_HPP

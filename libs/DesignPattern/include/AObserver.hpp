/*
** EPITECH PROJECT, 2026
** zappy
** File description:
** AObserver
*/

#ifndef ZAPPY_AOBSERVER_HPP
#define ZAPPY_AOBSERVER_HPP

#include <initializer_list>
#include <utility>
#include <vector>

#include "IObserver.hpp"
#include "ISubject.hpp"

namespace designPattern {
class AObserver: public IObserver {
public:
    explicit AObserver(
        const std::initializer_list<std::pair<int, ISubject &>> &subjects);

    ~AObserver() override;

protected:
    std::vector<std::pair<int, ISubject &>> _subjects;
};
} // designPattern

#endif //ZAPPY_AOBSERVER_HPP

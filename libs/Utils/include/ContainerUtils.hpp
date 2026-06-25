/*
** EPITECH PROJECT, 2026
** ZPY
** File description:
** ContainerUtils.hpp
*/

#pragma once

#include <queue>

template <class T, class S, class C>
static inline S& container(std::priority_queue<T, S, C>& q) {
    struct HackedQueue : private std::priority_queue<T, S, C> {
        static S& container(std::priority_queue<T, S, C>& q) {
            return q.*&HackedQueue::c;
        }
    };
return HackedQueue::container(q);
}
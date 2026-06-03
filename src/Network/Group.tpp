/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router::Group
*/

#pragma once
#include "constants.hpp"
#include "StringUtils.hpp"

namespace network {
template <typename TClientState>
Router<TClientState>::Group::Group(typename RadixTree::Node *node): _paths{node}
{}

template <typename TClientState>
void Router<TClientState>::Group::use(Handler handler)
{
    _middlewares.emplace_back(handler);
}

template <typename TClientState>
void Router<TClientState>::Group::get(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    const auto words = utils::StringUtils::split(_paths->word + path, '/');
    _paths->add(words, Method::GET, _middlewares, handlers);
}

template <typename TClientState>
void Router<TClientState>::Group::post(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    const auto words = utils::StringUtils::split(_paths->word + path, '/');
    _paths->add(words, Method::POST, _middlewares, handlers);
}

template <typename TClientState>
void Router<TClientState>::Group::put(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    const auto words = utils::StringUtils::split(_paths->word + path, '/');
    _paths->add(words, Method::PUT, _middlewares, handlers);
}

template <typename TClientState>
void Router<TClientState>::Group::delet(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    const auto words = utils::StringUtils::split(_paths->word + path, '/');
    _paths->add(words, Method::DELETE, _middlewares, handlers);
}

template <typename TClientState>
void Router<TClientState>::Group::use(
    std::initializer_list<Handler> middlewares)
{
    _middlewares.insert(_middlewares.end(), middlewares.begin(),
        middlewares.end());
}
}

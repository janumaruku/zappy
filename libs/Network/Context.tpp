/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Context
*/

#pragma once

#include "Router.tpp"

namespace network {
template <typename TClientState>
Router<TClientState>::Context::Context(const nlohmann::json &request,
    TClientState &state, ConnectedSocket *socket): _state{state},
    _socket{socket}
{
    _request  = request;
    _response = Response{};

    _middlewares.emplace_back([this](Context *) {
        next();
    });

    _currentHandler = _middlewares.begin();
}

template <typename TClientState> std::string Router<
    TClientState>::Context::path() const
{
    return _request.path;
}

template <typename TClientState>
void Router<TClientState>::Context::abortWithStatus(const StatusCode &code)
{
    _response.statusCode    = code;
    _response.statusMessage = STATUES.at(code);
    _response.body          = {};
}

template <typename TClientState>
void Router<TClientState>::Context::jsonp(const StatusCode &code,
    const nlohmann::json &body)
{
    _response.statusCode    = code;
    _response.statusMessage = STATUES.at(code);
    _response.body          = body;
}

template <typename TClientState>
nlohmann::json Router<TClientState>::Context::response() const noexcept
{
    return _response;
}

template <typename TClientState>
void Router<TClientState>::Context::addMiddleware(const Handler &middleware)
{
    _middlewares.push_back(middleware);

    if (!_middlewares.empty())
        _currentHandler = _middlewares.begin();
}

template <typename TClientState>
void Router<TClientState>::Context::addMiddlewares(
    const std::vector<Handler> &middlewares)
{
    _middlewares.insert(_middlewares.end(), middlewares.begin(),
        middlewares.end());

    if (!_middlewares.empty())
        _currentHandler = _middlewares.begin();
}

template <typename TClientState>
void Router<TClientState>::Context::setHandler(const Handler &handler)
{
    _handler = handler;
}

template <typename TClientState>
void Router<TClientState>::Context::addParams(
    const std::vector<std::pair<std::string, std::string>> &params)
{
    for (const auto &[key, value]: params)
        _params[key] = value;
}

template <typename TClientState>
void Router<TClientState>::Context::next()
{
    ++_currentHandler;
    if (_currentHandler != _middlewares.end())
        (*_currentHandler)(this);
    else
        _handler(this);
}

template <typename TClientState>
bool Router<TClientState>::Context::hasHandlers() const noexcept
{
    return _handler.empty();
}

template <typename TClientState>
const Request &Router<TClientState>::Context::getRequest() const noexcept
{
    return _request;
}

template <typename TClientState>
void Router<TClientState>::Context::error(const std::exception &err) noexcept
{
    _errors.emplace_back(err);
}
} // namespace network

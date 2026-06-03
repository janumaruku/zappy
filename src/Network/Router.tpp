/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router
*/

#pragma once

#include "jsonParser.hpp"
#include "Router.hpp"
#include "StringUtils.hpp"

namespace network {
inline std::ostream &operator<<(std::ostream &stream, const Method &method)
{
    switch (method) {
    case Method::GET:
        stream << "GET";
        break;
    case Method::POST:
        stream << "POST";
        break;
    case Method::PUT:
        stream << "PUT";
        break;
    case Method::DELETE:
        stream << "DELETE";
        break;
    default:
        break;
    }

    return stream;
}

template <typename TClientState> void Router<TClientState>::run()
{
    printPaths();
    std::cout << "[ROUTER-DEBUG] Listening and serving on port "
              << _port << " ...\n" << std::endl;
    startAccept();
    _ioContext.run();
}

template <typename TClientState>
void Router<TClientState>::get(
    const std::string &path, std::initializer_list<Handler> handlers)
{
    auto splitPath = utils::StringUtils::split(path, '/');
    _routes.add(splitPath, Method::GET, handlers);
}

template <typename TClientState>
void Router<TClientState>::post(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    auto splitPath = utils::StringUtils::split(path, '/');
    _routes.add(splitPath, Method::POST, handlers);
}

template <typename TClientState>
void Router<TClientState>::put(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    auto splitPath = utils::StringUtils::split(path, '/');
    _routes.add(splitPath, Method::PUT, handlers);
}

template <typename TClientState>
void Router<TClientState>::delet(const std::string &path,
    std::initializer_list<Handler> handlers)
{
    auto splitPath = utils::StringUtils::split(path, '/');
    _routes.add(splitPath, Method::DELETE, handlers);
}

template <typename TClientState>
void Router<TClientState>::use(Handler handler)
{
    _middlewares.emplace_back(handler);
}

template <typename TClientState>
void Router<TClientState>::use(std::initializer_list<Handler> handlers)
{
    _middlewares.insert(_middlewares.end(), handlers.begin(), handlers.end());
}

template <typename TClientState>
Router<TClientState>::Group Router<TClientState>::group(
    const std::string &prefix)
{
    const auto words               = utils::StringUtils::split(prefix, '/');
    typename RadixTree::Node *node = _routes.find(words);
    Group group{node};

    return group;
}

template <typename TClientState> void Router<TClientState>::startAccept()
{
    _acceptor.asyncAccept([this](const std::error_code &err,
        const std::shared_ptr<ConnectedSocket> &sock) {
            if (err) {
                std::cerr << err.message() << std::endl;
            } else {
                _clients[sock] = {};
                startClient(sock);
            }
            startAccept();
        });
}

template <typename TClientState>
void Router<TClientState>::startClient(
    const std::shared_ptr<ConnectedSocket> &sock)
{
    clientRead(sock.get());
}

template <typename TClientState>
void Router<TClientState>::handleTransmission(
    ConnectedSocket *socket, TClientState &clientState)
{
    const nlohmann::json stream = nlohmann::json::parse(_transmission);

    Context context{stream, clientState, socket};
    context.addMiddlewares(_middlewares);
    const StatusCode status = _routes.handle(context);

    if (status != StatusCode::STATUS_OK)
        context.abortWithStatus(status);
    else
        context.next();

    clientWrite(socket, context.response().dump());

    _transmission.clear();
}

template <typename TClientState>
void Router<TClientState>::handleRead(
    const size_t &bytes, ConnectedSocket *socket, TClientState &clientState)
{
    _readBuffer.resize(bytes);
    if (_readBuffer.ends_with("\r\n")) {
        _transmission.insert(
            _transmission.end(), _readBuffer.begin(), _readBuffer.end());
        _transmission.pop_back();
        _transmission.pop_back();
        handleTransmission(socket, clientState);
    } else {
        _transmission.insert(
            _transmission.end(), _readBuffer.begin(), _readBuffer.end());
    }
}

template <typename TClientState>
void Router<TClientState>::clientRead(
    ConnectedSocket *sock)
{
    _readBuffer.resize(1024);
    sock->asyncReadSome(buffer(_readBuffer, _readBuffer.size()),
        [this, sock](const std::error_code &err, const std::size_t &bytes) {
            if (err) {
                std::cerr << err.message() << std::endl;
                return;
            }
            const auto &temp = std::ranges::find_if(_clients,
                [sock](const auto &elem) {
                    return sock == elem.first.get();
                });
            handleRead(bytes, sock, temp->second);
        });
}

template <typename TClientState>
void Router<TClientState>::clientWrite(
    ConnectedSocket *sock, const std::string &message)
{
    _writeBuffer = message + "\r\n";
    sock->asyncWrite(buffer(_writeBuffer),
        [this, sock](
        const std::error_code &err, const std::size_t & /*bytes*/) {
            if (err) {
                std::cerr << err.message() << std::endl;
            }
            clientRead(sock);
        });
}

template <typename TClientState>
void Router<TClientState>::printPaths() const noexcept
{
    // std::vector<std::string> get;
    // std::vector<std::string> post;
    // std::vector<std::string> put;
    // std::vector<std::string> del;
    // _routes.getPaths(get, post, put, del);
    _routes.printPaths();
}
} // namespace network

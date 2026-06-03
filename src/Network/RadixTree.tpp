/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** RadixTree
*/

#pragma once

#include "constants.hpp"
#include "StringUtils.hpp"

namespace network {
template <typename TClientState>
Router<TClientState>::RadixTree::Node::Node(): word{"/"}, parent{nullptr}
{}

template <typename TClientState>
Router<TClientState>::RadixTree::Node::Node(const std::string &nodeWord,
    Node *nodeParent): word{nodeWord}, parent{nodeParent}
{}

template <typename TClientState>
void Router<TClientState>::RadixTree::Node::add(
    const std::vector<std::string> &words, const Method &method,
    const std::vector<Handler> middles,
    std::initializer_list<Handler> handles)
{
    Node *tempNode = this;
    for (std::size_t count = 1; count < words.size(); ++count) {
        const auto &word = words[count];
        if (!word.empty() && word[0] == ':') {
            if (!tempNode->param.empty() && tempNode->param != word) {
                std::cout << utils::RED << "Param already defined in this path: " <<
                    word << " | " << tempNode->param <<
                    utils::RESET << std::endl;
                return;
            }
            if (tempNode->paramNode == nullptr) {
                tempNode->param     = word;
                tempNode->paramNode = std::make_unique<Node>(word);
            }
            tempNode = tempNode->paramNode.get();
            continue;
        }
        if (!tempNode->children.contains(word))
            tempNode->children[word] = std::make_unique<Node>(word);
        tempNode = tempNode->children[word].get();
    }

    if (tempNode->handlers.contains(method)) {
        std::cout << utils::YELLOW << "Path " << std::quoted(
                "/" + utils::StringUtils::toString(words, '/')) <<
            " already registered for this method" << utils::RESET
            << std::endl;
        return;
    }

    if (!middles.empty() && tempNode->sharedMiddlewares.empty()) {
        tempNode->sharedMiddlewares.insert(tempNode->sharedMiddlewares.end(),
            middles.begin(), middles.end());
    }

    if (handles.size() > 1) {
        std::vector<Handler> &methodMids = tempNode->methodMiddlewares[method];
        methodMids.insert(methodMids.end(), handles.begin(),
            handles.begin() + handles.size() - 1);
    }

    if (handles.size() > 0) {
        tempNode->handlers[method] = *(handles.begin() + handles.size() - 1);
    }

    tempNode->methods.emplace_back(method);
}

template <typename TClientState>
void Router<TClientState>::RadixTree::Node::print(
    const Node *node) noexcept
{
    printHelper(node, "");
}

template <typename TClientState>
void Router<TClientState>::RadixTree::Node::printHelper(
    const Node *node, const std::string &path) noexcept
{
    std::string currentPath = path.empty() ? "/" + node->word : path + "/" + node->word;
    
    if (node->word.empty())
        currentPath = path;

    if (!node->handlers.empty()) {
        std::cout << currentPath << std::endl;
    }

    if (node->paramNode)
        printHelper(node->paramNode.get(), currentPath);

    for (const auto &[key, value]: node->children)
        printHelper(value.get(), currentPath);
}

template <typename TClientState>
void Router<TClientState>::RadixTree::add(const std::vector<std::string> &words,
    const Method &method, std::initializer_list<Handler> handlers)
{
    if (words.empty())
        return;

    if (!_root.contains(words[0]))
        _root[words[0]] = std::make_unique<Node>(words[0]);
    Node *tempNode = _root.at(words[0]).get();

    tempNode->add(words, method, {}, handlers);
}

template <typename TClientState>
StatusCode Router<TClientState>::RadixTree::handle(Context &context)
{
    auto path = context.path();
    Method method = context.getRequest().method;
    Node *node;
    std::vector<Handler> middlewares;
    std::vector<std::pair<std::string, std::string>> params;
    
    if (path.empty() || path[0] != '/') {
        node = nullptr;
    } else {
        node = find(utils::StringUtils::split(&path[1], '/'), method, 
            middlewares, params);
    }

    if (node == nullptr)
        return StatusCode::NOT_FOUND;
    if (!node->handlers.contains(method))
        return StatusCode::METHOD_NOT_ALLOWED;

    context.addMiddlewares(middlewares);
    context.setHandler(node->handlers.at(method));
    context.addParams(params);

    return StatusCode::STATUS_OK;
}

template <typename TClientState>
Router<TClientState>::RadixTree::Node *Router<TClientState>::RadixTree
::find(const std::vector<std::string> &words)
{
    const auto itt = std::ranges::find_if(_root, [words](const auto &elem) {
        return words[0] == elem.first;
    });
    if (itt == _root.end()) {
        return nullptr;
    }

    Node *res = itt->second.get();
    for (std::size_t count = 1; count < words.size(); ++count) {
        if (res->children.contains(words[count]))
            res = res->children.at(words[count]).get();
        else if (res->paramNode)
            res = res->paramNode.get();
        else
            return nullptr;
    }

    return res;
}

template <typename TClientState>
void Router<TClientState>::RadixTree::Node::collectRoutes(
    const Node *node, const std::string &path,
    std::vector<std::pair<Method, std::string>> &routes) noexcept
{
    std::string currentPath = path.empty() ? "/" + node->word : path + "/" + node->word;

    if (node->word.empty())
        currentPath = path;

    // Collect all methods registered at this node
    for (const auto &[method, handler] : node->handlers) {
        routes.emplace_back(method, currentPath);
    }

    if (node->paramNode)
        collectRoutes(node->paramNode.get(), currentPath, routes);

    for (const auto &[key, value] : node->children)
        collectRoutes(value.get(), currentPath, routes);
}

template <typename TClientState>
void Router<TClientState>::RadixTree::printPaths() const noexcept
{
    std::vector<std::pair<Method, std::string>> routes;

    for (const auto &node : std::ranges::views::values(_root)) {
        Node::collectRoutes(node.get(), "", routes);
    }

    std::ranges::sort(routes, [](const auto &a, const auto &b) {
        if (a.second != b.second)
            return a.second < b.second;
        return a.first < b.first;
    });

    auto methodToString = [](Method m) -> std::string {
        switch (m) {
        case Method::GET:    return "GET   ";
        case Method::POST:   return "POST  ";
        case Method::PUT:    return "PUT   ";
        case Method::DELETE: return "DELETE";
        default:             return "???   ";
        }
    };

    for (const auto &[method, path] : routes) {
        std::cout << "[ROUTER-DEBUG] " << methodToString(method) << " " << path << std::endl;
    }
}

template <typename TClientState>
Router<TClientState>::RadixTree::Node *Router<TClientState>::RadixTree
::find(const std::vector<std::string> &words, const Method &method,
    std::vector<Handler> &middlewares,
    std::vector<std::pair<std::string, std::string>> &params)
{
    const auto itt = std::ranges::find_if(_root, [&words](const auto &elem) {
        return words[0] == elem.first;
    });
    if (itt == _root.end()) {
        return nullptr;
    }

    Node *res = itt->second.get();
    middlewares.insert(middlewares.end(), res->sharedMiddlewares.begin(),
        res->sharedMiddlewares.end());
    
    for (std::size_t count = 1; count < words.size(); ++count) {
        if (res->children.contains(words[count])) {
            res = res->children.at(words[count]).get();
        } else if (res->paramNode) {
            params.emplace_back(res->param, words[count]);
            res = res->paramNode.get();
        } else {
            middlewares.clear();
            return nullptr;
        }
        middlewares.insert(middlewares.end(), res->sharedMiddlewares.begin(),
            res->sharedMiddlewares.end());
    }
    
    if (res->methodMiddlewares.contains(method)) {
        const auto &methodMids = res->methodMiddlewares.at(method);
        middlewares.insert(middlewares.end(), methodMids.begin(), methodMids.end());
    }

    return res;
}
}

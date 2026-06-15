/*
** EPITECH PROJECT, 2026
** my_teams
** File description:
** Router
*/

#ifndef MY_TEAMS_ROUTER_HPP
#define MY_TEAMS_ROUTER_HPP

#include "Acceptor.hpp"
#include "IoContext.hpp"
#include "jsonParser.hpp"
#include "Serializer.hpp"

namespace network {
const std::unordered_map<StatusCode, std::string> STATUES = {
    {StatusCode::STATUS_OK, "Status OK"},
    {StatusCode::UNAUTHORIZED, "Unauthorised"},
    {StatusCode::NOT_FOUND, "Not Found"},
    {StatusCode::METHOD_NOT_ALLOWED, "Methode Not Allowed"}
};

std::ostream &operator<<(std::ostream &stream, const Method &method);

template <typename TClientState>
class Router {
public:
    class Context;
    using Handler = std::function<void(Context *)>;

    class Context {
    public:
        Context(const nlohmann::json &request, TClientState &state,
            ConnectedSocket *socket);

        std::string path() const;

        void abortWithStatus(const StatusCode &code);

        void jsonp(const StatusCode &code, const nlohmann::json &body);

        nlohmann::json response() const noexcept;

        void addMiddleware(const Handler &middleware);

        void addMiddlewares(const std::vector<Handler> &middlewares);

        void setHandler(const Handler &handler);

        void addParams(
            const std::vector<std::pair<std::string, std::string>> &params);

        void next();

        bool hasHandlers() const noexcept;

        const Request &getRequest() const noexcept;

        void error(const std::exception &err) noexcept;

        TClientState &getClientState()
        {
            return _state;
        }

    private:
        Request _request;
        Response _response;
        std::unordered_map<std::string, std::string> _params;
        TClientState &_state;
        ConnectedSocket *_socket;
        std::vector<Handler> _middlewares;
        Handler _handler;
        std::vector<Handler>::iterator _currentHandler;
        std::vector<std::exception> _errors;
    };

private:
    class RadixTree {
    public:
        using MethodMiddleWareMap = std::unordered_map<Method, std::vector<
            Handler>>;

        struct Node {
            Node();

            explicit Node(const std::string &nodeWord,
                Node *nodeParent = nullptr);

            void add(const std::vector<std::string> &words,
                const Method &method, const std::vector<Handler> middles,
                std::initializer_list<Handler> handles);

            static void print(const Node *node) noexcept;

            static void printHelper(const Node *node,
                const std::string &path) noexcept;

            static void collectRoutes(const Node *node, const std::string &path,
                std::vector<std::pair<Method, std::string>> &routes) noexcept;

            std::string word;
            Node *parent;
            std::string param;
            std::unique_ptr<Node> paramNode = nullptr;
            std::unordered_map<std::string, std::unique_ptr<Node>> children;
            std::unordered_map<Method, Handler> handlers;
            MethodMiddleWareMap methodMiddlewares;
            std::vector<Handler> sharedMiddlewares;
            std::vector<Method> methods;
        };

        using RootDictionary = std::unordered_map<std::string, std::unique_ptr<
            Node>>;

        void add(const std::vector<std::string> &words,
            const Method &method, std::initializer_list<Handler> handlers);

        StatusCode handle(Context &context);

        Node *find(const std::vector<std::string> &words);

        const RootDictionary &getRoot() const
        {
            return _root;
        }

        void printPaths() const noexcept;

    private:
        RootDictionary _root;

        Node *find(const std::vector<std::string> &words, const Method &method,
            std::vector<Handler> &middlewares, std::
            vector<std::pair<std::string, std::string>> &params);
    };

public:
    class Group {
    public:
        explicit Group(RadixTree::Node *node);

        void get(const std::string &path,
            std::initializer_list<Handler> handlers);

        void post(const std::string &path,
            std::initializer_list<Handler> handlers);

        void put(const std::string &path,
            std::initializer_list<Handler> handlers);

        void delet(const std::string &path,
            std::initializer_list<Handler> handlers);

        void use(Handler handler);

        void use(std::initializer_list<Handler> middlewares);

    private:
        RadixTree::Node *_paths;
        std::vector<Handler> _middlewares;
    };

    explicit Router(const int &port): _acceptor{_ioContext, Endpoint{port}},
        _port{port}
    {}

    void run();

    void get(const std::string &path, std::initializer_list<Handler> handlers);

    void post(const std::string &path, std::initializer_list<Handler> handlers);

    void put(const std::string &path, std::initializer_list<Handler> handlers);

    void delet(const std::string &path,
        std::initializer_list<Handler> handlers);

    void use(Handler handler);

    void use(std::initializer_list<Handler> handlers);

    Group group(const std::string &prefix);

private:
    IOContext _ioContext{};
    Acceptor _acceptor;
    int _port;
    std::unordered_map<std::shared_ptr<ConnectedSocket>, TClientState> _clients;
    std::string _readBuffer;
    std::string _writeBuffer;
    std::string _transmission;
    RadixTree _routes;
    std::vector<Handler> _middlewares;

    void startAccept();

    void startClient(const std::shared_ptr<ConnectedSocket> &sock);

    void handleTransmission(ConnectedSocket *socket, TClientState &clientState);

    void handleRead(const size_t &bytes, ConnectedSocket *socket,
        TClientState &clientState);

    void clientRead(ConnectedSocket *sock);

    void clientWrite(ConnectedSocket *sock, const std::string &message);

    void printPaths() const noexcept;
};

} // namespace network

#endif // MY_TEAMS_ROUTER_HPP

#include "../Context.tpp"
#include "../Group.tpp"
#include "../RadixTree.tpp"
#include "../Router.tpp"

#include <iostream>
#include <memory>
#include <vector>
#include "Acceptor.hpp"
#include "IoContext.hpp"
#include "Buffer.hpp"

void startAccept(network::Acceptor &acceptor);
void startClient(const std::shared_ptr<network::ConnectedSocket> &socket);
void handleRead(const std::shared_ptr<network::ConnectedSocket> &socket,
                std::shared_ptr<std::vector<char>> buf);
void handleWrite(const std::shared_ptr<network::ConnectedSocket> &socket,
                 std::shared_ptr<std::vector<char>> buf);

int main()
{
    network::IOContext ioContext;
    network::Acceptor acceptor(ioContext, network::Endpoint{8080, "127.0.0.1"});

    startAccept(acceptor);
    ioContext.run();
    return 0;
}

void startAccept(network::Acceptor &acceptor)
{
    acceptor.asyncAccept([&acceptor](const std::error_code &error,
        const std::shared_ptr<network::ConnectedSocket> &socket) {
            if (error) {
                std::cerr << "Accept error: " << error.message() << '\n';
                startAccept(acceptor);
                return;
            }
            startClient(socket);
            startAccept(acceptor); // re-arm
        });
}

void startClient(const std::shared_ptr<network::ConnectedSocket> &socket)
{
    // The buffer is heap-allocated and owned by a shared_ptr so that it
    // outlives every async operation that holds a raw pointer into it.
    auto buf = std::make_shared<std::vector<char>>(1024);
    handleRead(socket, buf);
}

void handleRead(const std::shared_ptr<network::ConnectedSocket> &socket,
                std::shared_ptr<std::vector<char>> buf)
{
    socket->asyncReadSome(network::buffer(*buf),
        [socket, buf](const std::error_code &error, const std::size_t &n) {
            if (error) {
                std::cerr << "Read error: " << error.message() << '\n';
                socket->close();
                return;
            }
            std::cout << "Received: " << std::string(buf->data(), n) << '\n';
            handleWrite(socket, buf);
        });
}

void handleWrite(const std::shared_ptr<network::ConnectedSocket> &socket,
                 std::shared_ptr<std::vector<char>> buf)
{
    // The response must also be heap-allocated: asyncWrite stores a raw
    // ConstBuffer pointer, so a stack string would dangle before the write
    // completes. Capturing the shared_ptr in the lambda keeps it alive.
    auto response = std::make_shared<std::string>("Message received\r\n");
    socket->asyncWrite(network::buffer(*response),
        [socket, buf, response](const std::error_code &error,
            const std::size_t &) {
            if (error) {
                std::cerr << "Write error: " << error.message() << '\n';
                socket->close();
                return;
            }
            handleRead(socket, buf); // back to read — circular
        });
}
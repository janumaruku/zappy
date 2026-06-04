#include "Acceptor.hpp"
#include "IoContext.hpp"

void startAccept(const network::Acceptor &acceptor);

int main()
{
    network::IOContext ioContext;
    const network::Acceptor acceptor(ioContext,
        network::Endpoint{8080, "127.0.0.1"});

    startAccept(acceptor);
    ioContext.run();
    return 0;
}

void startAccept(network::Acceptor &acceptor)
{
    acceptor.asyncAccept([acceptor](const std::error_code &error,
        const std::shared_ptr<network::ConnectedSocket> &socket) {
            if (error) {
                std::cerr << "Error accepting client: " << error.message() <<
                    '\n';
                startAccept(acceptor);
                return;
            }

            const network::Endpoint endpoint = socket->remoteEndpoint();

            std::cout << "Accepted client: " << endpoint.getHostname() << ":"
                << endpoint.getPort() << '\n';

            startAccept(acceptor);
        });
}

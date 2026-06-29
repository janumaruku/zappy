#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>
#include <poll.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int listeningFd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(listeningFd, (sockaddr*)&addr, sizeof(addr));
    listen(listeningFd, 10);
    std::clog << "Listening on port " << PORT << std::endl;

    std::vector<pollfd> fds;
    fds.push_back({listeningFd, POLLIN, 0});

    while (true) {
        poll(fds.data(), fds.size(), 10); // blocks until at least one fd is ready

        if (fds[0].revents & POLLIN) { // listening socket: new connection ready
            sockaddr_in clientAddr;
            socklen_t clientAddrLen = sizeof(clientAddr);
            int clientFd = accept(listeningFd, (sockaddr*)&clientAddr, &clientAddrLen);
            fds.push_back({clientFd, POLLIN, 0}); // watch the new client
            std::clog << "New connection accepted" << std::endl;
        }

        for (std::size_t i = 1; i < fds.size(); ++i) {
            if (!(fds[i].revents & POLLIN))
                continue;

            char buf[BUFFER_SIZE];
            ssize_t n = read(fds[i].fd, buf, BUFFER_SIZE);

            if (n <= 0) { // client disconnected
                close(fds[i].fd);
                fds.erase(fds.begin() + static_cast<long>(i));
                --i;
                continue;
            }

            std::clog << "Read " << n << " bytes, content: " << buf << std::endl;

            std::string message = "Message received";
            write(fds[i].fd, message.c_str(), message.size());
        }
    }

    return 0;
}